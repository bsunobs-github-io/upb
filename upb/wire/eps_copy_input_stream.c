/*
 * Copyright (c) 2009-2021, Google LLC
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Google LLC nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL Google LLC BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "upb/wire/eps_copy_input_stream.h"

#include "upb/wire/reader.h"
#include "upb/wire/types.h"

// Must be last.
#include "upb/port/def.inc"

// We frequently reference this constant in this file.
#define kSlopBytes kUpb_EpsCopyInputStream_SlopBytes

static const char* _upb_EpsCopyInputStream_NoOpCallback(
    upb_EpsCopyInputStream* e, const char* old_end, const char* new_start) {
  return new_start;
}

const char* _upb_EpsCopyInputStream_IsDoneFallbackNoCallback(
    upb_EpsCopyInputStream* e, const char* ptr, int overrun) {
  return _upb_EpsCopyInputStream_IsDoneFallbackInline(
      e, ptr, overrun, _upb_EpsCopyInputStream_NoOpCallback);
}

// Only call if at start of tag.
// Currently we check for terminating 0 but not end-group.
static bool _upb_EpsCopyInputStream_ParseEndsInSlopRegion(const char* ptr,
                                                          const char* end) {
  fprintf(stderr, "ParseEndsInSlopRegion()\n");
  while (ptr < end) {
    uint32_t tag;
    ptr = upb_WireReader_ReadTag(ptr, &tag);
    if (!ptr || ptr > end) return false;
    // ending on 0 tag is allowed and is the major reason for the necessity of
    // this function.
    if (tag == 0) {
      fprintf(stderr, "Zero tag in slop region!\n");
      return true;
    }
    switch (upb_WireReader_GetWireType(tag)) {
      case kUpb_WireType_Varint: {
        uint64_t val;
        ptr = upb_WireReader_ReadVarint(ptr, &val);
        if (!ptr) return false;
        break;
      }
      case kUpb_WireType_32Bit:
        ptr += 4;
        break;
      case kUpb_WireType_64Bit:
        ptr += 8;
        break;
      case kUpb_WireType_Delimited: {
        int32_t size;
        ptr = upb_WireReader_ReadSize(ptr, &size);
        if (!ptr || size > end - ptr) return false;
        ptr += size;
        break;
      }
      case kUpb_WireType_StartGroup:
      case kUpb_WireType_EndGroup:
        break;
      default:
        return false;  // Unknown wireformat
    }
  }
  return false;
}

static char* _upb_EpsCopyInputStream_AppendNextChunk(upb_EpsCopyInputStream* e,
                                                     char* ptr) {
  UPB_ASSERT(e->next_chunk);
  UPB_ASSERT(e->next_chunk_size < kSlopBytes);
  fprintf(stderr, "Append chunk data=%.*s, size=%zu\n", (int)e->next_chunk_size,
          e->next_chunk, e->next_chunk_size);
  upb_EpsCopyInputStream_SmallMemcpy(ptr, e->next_chunk, e->next_chunk_size);
  e->next_chunk = NULL;
  return ptr + e->next_chunk_size;
}

const char* _upb_EpsCopyInputStream_FillPatchBuffer(upb_EpsCopyInputStream* e,
                                                    int have) {
  char* start = e->patch + have;
  char* ptr = start;
  char* end = e->patch + kSlopBytes;
  ptr = _upb_EpsCopyInputStream_AppendNextChunk(e, ptr);
  while (1) {
    if (_upb_EpsCopyInputStream_ParseEndsInSlopRegion(e->patch, ptr) ||
        !_upb_EpsCopyInputStream_NextBuffer(e)) {
      // We are at end-of-stream, so all of the remaining slop bytes will have
      // indeterminate value.
      e->end = ptr;
      e->limit = 0;
      fprintf(stderr, "YO0\n");
      break;
    }
    if (e->next_chunk_size >= kSlopBytes) {
      // We got a big buffer (enough to satisfy all the slop and then some) so
      // we are done, and moreover we can leave e->next_chunk for the next time
      // we need more data.
      fprintf(stderr, "Oh we are set, buffer size=%zu\n", e->next_chunk_size);
      memcpy(ptr, e->next_chunk, kSlopBytes);
      e->end = ptr;
      e->limit -= e->end - start;
      e->next_chunk = NULL;
      fprintf(stderr, "YO1\n");
      break;
    }
    ptr = _upb_EpsCopyInputStream_AppendNextChunk(e, ptr);
    if (ptr > end) {
      // We have enough data to provide kSlopBytes of overflow, so we are done.
      //
      // We could theoretically keep filling as long as there is more space in
      // the patch buffer. However if we get a big chunk in the second half of
      // the patch buffer, we would no longer be able to provide the invariant
      // that e->next_chunk corresponds to the same stream position as e->end,
      // which would complicate the logic and probably penalize the speed of the
      // more common case where stream buffers are >kSlopBytes bytes long.
      e->end = ptr - kSlopBytes;
      e->limit -= e->end - start;
      fprintf(stderr, "YO2\n");
      break;
    }
  }
  e->limit_ptr = e->end + UPB_MIN(e->limit, 0);
  e->aliasing_delta = kUpb_EpsCopyInputStream_CannotAlias;
  fprintf(stderr, "Finishing FillPatchBuffer(), available data=%d\n",
          (int)(e->end - e->patch));
  return e->patch;
}

#if 0
const char* _upb_EpsCopyInputStream_NextBuffer(upb_EpsCopyInputStream* e,
                                               int overrun) {
  fprintf(stderr, "NextBuffer()\n");
  if (e->next_chunk == NULL) return NULL;  // We've reached end of stream.
  if (e->next_chunk != e->patch) {
    assert(e->next_chunk_size > kSlopBytes);
    // The chunk is large enough to be used directly
    e->end =
        e->next_chunk + e->next_chunk_size - kSlopBytes;
    const char* res = e->next_chunk;
    e->next_chunk = e->patch;
    if (e->aliasing == kUpb_EpsCopyInputStream_OnPatch) {
      e->aliasing = kUpb_EpsCopyInputStream_NoDelta;
    }
    return res;
  }
  // Move the slop bytes of previous buffer to start of the patch buffer.
  // Note we must use memmove because the previous buffer could be part of
  // buffer_.
  memmove(e->patch, e->end, kSlopBytes);
  if (!_upb_EpsCopyInputStream_ParseEndsInSlopRegion(e->patch, overrun)) {
    size_t size;
    upb_Status status;
    upb_Status_Clear(&status);
    const void* data = upb_ZeroCopyInputStream_Next(e->zcis, &size, &status);
    fprintf(stderr, "Got ZCIS buffer p=%p, size=%zu\n", data, size);

    if (size > kSlopBytes) {
      // We got a large chunk
      memcpy(e->patch + kSlopBytes, data, kSlopBytes);
      e->next_chunk = data;
      e->end = e->patch + kSlopBytes;
      if (e->aliasing >= kUpb_EpsCopyInputStream_NoDelta) {
        e->aliasing = kUpb_EpsCopyInputStream_OnPatch;
      }
      return e->patch;
    } else if (size > 0) {
      memcpy(e->patch + kSlopBytes, data, size);
      e->next_chunk = e->patch;
      e->end = e->patch + size;
      if (e->aliasing >= kUpb_EpsCopyInputStream_NoDelta) {
        e->aliasing = kUpb_EpsCopyInputStream_OnPatch;
      }
      return e->patch;
    }
  }

  // End of stream or array
  if (e->aliasing == kUpb_EpsCopyInputStream_NoDelta) {
    // If there is no more block and aliasing is true, the previous block
    // is still valid and we can alias. We have users relying on string_view's
    // obtained from protos to outlive the proto, when the parse was from an
    // array. This guarantees string_view's are always aliased if parsed from
    // an array.
    e->aliasing = (uintptr_t)e->end - (uintptr_t)e->patch;
  }
  e->next_chunk = NULL;
  e->end = e->patch + kSlopBytes;
  e->next_chunk_size = 0;
  return e->patch;
}
#endif

#undef kSlopBytes
