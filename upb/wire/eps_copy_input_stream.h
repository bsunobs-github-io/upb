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

#ifndef UPB_WIRE_EPS_COPY_INPUT_STREAM_H_
#define UPB_WIRE_EPS_COPY_INPUT_STREAM_H_

#include <limits.h>
#include <string.h>

#include "upb/base/string_view.h"
#include "upb/io/zero_copy_input_stream.h"
#include "upb/mem/arena.h"

// Must be last.
#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

// The maximum number of bytes a single protobuf field can take up in the
// wire format.  We only want to do one bounds check per field, so the input
// stream guarantees that after upb_EpsCopyInputStream_IsDone() is called,
// the decoder can read this many bytes without performing another bounds
// check.  The stream will copy into a patch buffer as necessary to guarantee
// this invariant.
#define kUpb_EpsCopyInputStream_SlopBytes 16

// We reference this constant a lot, so create a local alias and undef later.
#define kSlopBytes kUpb_EpsCopyInputStream_SlopBytes

typedef enum {
  kUpb_EpsCopyInputStream_CannotAlias = -1,
} upb_EpsCopyInpuStream_AliasingConstants;

typedef struct {
  upb_ZeroCopyInputStream* zcis;

  // This is the end-of-buffer pointer for the purpose of bounds checks, but it
  // is not the true buffer end. We always ensure that at least kSlopBytes
  // beyond this can be safely read without reading unallocated or uninitialized
  // data.
  //
  // The data beyond `end` must always represent the true next bytes of the
  // stream, if any such bytes exist.  If we are at the end of the stream, the
  // bytes after `end` will have undetermined value.  The stream will report an
  // error if the user reads past the end of the stream.
  const char* end;

  // This is the pointer we use for bounds checks. It is similar to `end`, but
  // it also takes into account pushed limits, so it may be smaller than `end`.
  // When the pointer reaches `limit_ptr`, we have hit either a pushed limit or
  // end-of-buffer. This should always be exactly equal to:
  //    end + UPB_MIN(limit, 0)
  const char* limit_ptr;

  // The next unconsumed chunk from the upb_ZeroCopyInputStream, or NULL if
  // we do not currently have one.  If present, this corresponds to the same
  // stream position as `end`, and the data after `end` must perfectly match
  // the first kSlopBytes of this buffer.  This also implies that next_chunk
  // must always be at least kSlopBytes long.
  const char* next_chunk;

  // The size of the `next_chunk` buffer. Must be >= kSlopBytes. If `next_chunk`
  // is NULL then the contents of this field are undefined.
  size_t next_chunk_size;

  // A delta that we can add to the current `ptr` to get the corresponding
  // pointer into an input buffer, or kUpb_EpsCopyInputStream_CannotAlias if the
  // patch buffer spans multiple input buffers.
  //
  // If we are currently parsing from an actual input buffer this will be zero.
  // If we are parsing from the patch buffer, but this is the final buffer of
  // the stream, this will be a nonzero delta between the patch buffer and the
  // input buffer. Otherwise this will be kUpb_EpsCopyInputStream_CannotAlias
  // because the patch buffer contains data from multiple input buffers.
  uintptr_t aliasing_delta;

  // The current submessage limit relative to `end`. This can be negative, zero,
  // or positive, depending on whether the current limit is before, equal to, or
  // beyond the current `end`.
  //
  // This must be an integer and not a pointer, because we cannot safely
  // construct pointers that are beyond the current buffer (even if we could,
  // they would be vulnerable to wrapping).
  int limit;

  // Returns true if the stream encountered an error (either from the input
  // stream of from reading beyond a limit).
  bool error;

  // Whether the user enabled aliasing when constructing the stream.
  bool enable_aliasing;

  // The patch buffer.  We copy data into this when we cross buffer boundaries
  // or when the input buffers are too small, to construct contiguous regions
  // of input data.
  char patch[kSlopBytes * 2];
} upb_EpsCopyInputStream;

// Returns true if the stream is in the error state. A stream enters the error
// state when the user reads past a limit (caught in IsDone()) or the
// ZeroCopyInputStream returns an error.
UPB_INLINE bool upb_EpsCopyInputStream_IsError(upb_EpsCopyInputStream* e) {
  return e->error;
}

typedef const char* upb_EpsCopyInputStream_BufferFlipCallback(
    upb_EpsCopyInputStream* e, const char* old_end, const char* new_start);

typedef const char* upb_EpsCopyInputStream_IsDoneFallbackFunc(
    upb_EpsCopyInputStream* e, const char* ptr, int overrun);

// A potentially specialized memcpy() for copies smaller than kSlopBytes. We use
// this in several cases where we need memcpy() a small amount of data (less
// than kSlopBytes) but the size is not known at compile time. Normally such
// a call would require an out-of-line call to a fully generalized memcpy(), but
// we may be able to write an inlinable version that will do better.
UPB_INLINE void upb_EpsCopyInputStream_SmallMemcpy(void* __restrict dst,
                                                   const void* __restrict src,
                                                   size_t n) {
  UPB_ASSUME(n < kSlopBytes);
  memcpy(dst, src, n);
}

UPB_INLINE void _upb_EpsCopyInputStream_CheckLimit(upb_EpsCopyInputStream* e) {
  UPB_ASSERT(e->limit_ptr == e->end + UPB_MIN(0, e->limit));
}

UPB_INLINE bool _upb_EpsCopyInputStream_NextBuffer(upb_EpsCopyInputStream* e) {
  UPB_ASSERT(!e->next_chunk);
  upb_Status status;
  upb_Status_Clear(&status);
  e->next_chunk = (const char*)upb_ZeroCopyInputStream_Next(
      e->zcis, &e->next_chunk_size, &status);
  return e->next_chunk != NULL;
}

const char* _upb_EpsCopyInputStream_FillPatchBuffer(upb_EpsCopyInputStream* e,
                                                    int have);

// Initializes a upb_EpsCopyInputStream using the contents of the buffer
// [*ptr, size].  Updates `*ptr` as necessary to guarantee that at least
// kUpb_EpsCopyInputStream_SlopBytes are available to read.
UPB_INLINE const char* upb_EpsCopyInputStream_Init(
    upb_EpsCopyInputStream* e, const char* ptr, size_t size,
    upb_ZeroCopyInputStream* zcis, bool enable_aliasing) {
  e->next_chunk = NULL;
  e->zcis = zcis;
  e->error = false;
  e->enable_aliasing = enable_aliasing;
  memset(e->patch, 0, sizeof(e->patch));
  if (size <= kSlopBytes) {
    if (size) upb_EpsCopyInputStream_SmallMemcpy(&e->patch, ptr, size);
    e->end = e->patch + size;
    e->limit = 0;
    e->aliasing_delta = (uintptr_t)ptr - (uintptr_t)e->patch;
    ptr = e->patch;
    if (zcis) {
      if (UPB_LIKELY(_upb_EpsCopyInputStream_NextBuffer(e) &&
                     e->next_chunk_size >= kSlopBytes)) {
        memcpy(e->patch + size, e->next_chunk, kSlopBytes);
      } else {
        e->limit = INT_MAX - size;
        return _upb_EpsCopyInputStream_FillPatchBuffer(e, size);
      }
    }
  } else {
    e->end = ptr + size - kSlopBytes;
    e->limit = kSlopBytes;
    e->aliasing_delta = 0;
  }
  e->limit_ptr = e->end;
  if (zcis) e->limit = INT_MAX - size;
  return ptr;
}

UPB_INLINE const char* _upb_EpsCopyInputStream_DoIsDoneFallbackInline(
    upb_EpsCopyInputStream* e, const char* ptr, int overrun) {
  // fprintf(stderr, "DoIsDoneFallbackInline(), zcis=%p, overrun=%d\n", e->zcis,
  // overrun);
  if (UPB_UNLIKELY(overrun > e->limit)) return NULL;  // Parsed beyond limit.

  _upb_EpsCopyInputStream_CheckLimit(e);
  UPB_ASSERT(overrun < e->limit);
  UPB_ASSERT(overrun < kSlopBytes);
  UPB_ASSERT(e->limit > 0);
  UPB_ASSERT(e->limit_ptr == e->end);

  if (e->next_chunk) {
    // Fast path: the next chunk is ready.
    fprintf(stderr, "Fast path! Another buffer of size %zu is available.\n",
            e->next_chunk_size);
    ptr = e->next_chunk + overrun;
    e->end = e->next_chunk + e->next_chunk_size - kSlopBytes;
    e->limit -= e->next_chunk_size;
    e->limit_ptr = e->end + UPB_MIN(e->limit, 0);
    e->next_chunk = NULL;
    e->aliasing_delta = 0;
    return ptr;
  }

  // We need to build a patch buffer. Speculatively assume that we will be able
  // to fill the patch buffer to its full capacity with at most one stream
  // buffer. We copy the old slop region to the first half of the patch, and
  // fill the second half with more data (or nothing in the case of EOF). This
  // effectively advances e->end by kSlopBytes.
  fprintf(stderr, "Speculatively building a patch buffer.\n");
  const char* new_start = &e->patch[0] + overrun;
  memcpy(e->patch, e->end, kSlopBytes);
  e->end = &e->patch[kSlopBytes];
  e->limit -= kSlopBytes;
  e->limit_ptr = e->end + UPB_MIN(e->limit, 0);

  if (UPB_LIKELY(!e->zcis) || !_upb_EpsCopyInputStream_NextBuffer(e)) {
    // We are in the patch buffer, but at end-of-stream so the patch buffer
    // aliasing to one single input buffer.
    fprintf(stderr, "End of stream.\n");
    e->aliasing_delta = (uintptr_t)ptr - (uintptr_t)new_start;
    return new_start;
  }

  if (UPB_LIKELY(e->next_chunk_size >= kSlopBytes)) {
    fprintf(stderr, "Big enough next chunk!\n");
    e->aliasing_delta = kUpb_EpsCopyInputStream_CannotAlias;
    memcpy(e->patch + kSlopBytes, e->next_chunk, kSlopBytes);
    return new_start;
  }

  memmove(e->patch, e->patch + overrun, kSlopBytes);
  e->limit -= overrun;
  fprintf(stderr, "Fallback, next chunk too small!\n");
  return _upb_EpsCopyInputStream_FillPatchBuffer(e, kSlopBytes - overrun);
}

UPB_INLINE const char* _upb_EpsCopyInputStream_IsDoneFallbackInline(
    upb_EpsCopyInputStream* e, const char* ptr, int overrun,
    upb_EpsCopyInputStream_BufferFlipCallback* callback) {
  // fprintf(stderr, "IsDoneFallbackInline(), overrun=%d\n", overrun);
  const char* new_start =
      _upb_EpsCopyInputStream_DoIsDoneFallbackInline(e, ptr, overrun);
  fprintf(stderr, "e->limit_ptr - new_start=%d, limit=%d\n",
          (int)(e->limit_ptr - new_start), e->limit);
  UPB_ASSERT(new_start < e->limit_ptr);
  if (new_start) {
    return callback(e, ptr, new_start);
  } else {
    e->error = true;
    return callback(e, NULL, NULL);
  }
}

typedef enum {
  // The current stream position is at a limit.
  kUpb_IsDoneStatus_Done,

  // The current stream position is not at a limit.
  kUpb_IsDoneStatus_NotDone,

  // The current stream position is not at a limit, and the stream needs to
  // be flipped to a new buffer before more data can be read.
  kUpb_IsDoneStatus_NeedFallback,
} upb_IsDoneStatus;

// Returns the status of the current stream position.  This is a low-level
// function, it is simpler to call upb_EpsCopyInputStream_IsDone() if possible.
UPB_INLINE upb_IsDoneStatus upb_EpsCopyInputStream_IsDoneStatus(
    upb_EpsCopyInputStream* e, const char* ptr, int* overrun) {
  *overrun = ptr - e->end;
  // fprintf(stderr, "IsDoneStatus(): overrun=%d, limit=%d, limit overrun=%d\n",
  //         *overrun, e->limit, (int)(ptr - e->limit_ptr));
  if (UPB_LIKELY(ptr < e->limit_ptr)) {
    return kUpb_IsDoneStatus_NotDone;
  } else if (UPB_LIKELY(*overrun == e->limit)) {
    return kUpb_IsDoneStatus_Done;
  } else {
    return kUpb_IsDoneStatus_NeedFallback;
  }
}

// Returns true if the stream has hit a limit, either the current delimited
// limit or the overall end-of-stream. As a side effect, this function may flip
// the pointer to a new buffer if there are less than kSlopBytes of data to be
// read in the current buffer.
//
// Postcondition: if the function returns false, there are at least kSlopBytes
// of data available to read at *ptr.
UPB_INLINE bool upb_EpsCopyInputStream_IsDoneWithCallback(
    upb_EpsCopyInputStream* e, const char** ptr,
    upb_EpsCopyInputStream_IsDoneFallbackFunc* func) {
  int overrun;
  switch (upb_EpsCopyInputStream_IsDoneStatus(e, *ptr, &overrun)) {
    case kUpb_IsDoneStatus_Done:
      return true;
    case kUpb_IsDoneStatus_NotDone:
      return false;
    case kUpb_IsDoneStatus_NeedFallback:
      *ptr = func(e, *ptr, overrun);
      return *ptr == NULL;
  }
  UPB_UNREACHABLE();
}

const char* _upb_EpsCopyInputStream_IsDoneFallbackNoCallback(
    upb_EpsCopyInputStream* e, const char* ptr, int overrun);

// A simpler version of IsDoneWithCallback() that does not support a buffer flip
// callback. Useful in cases where we do not need to insert custom logic at
// every buffer flip.
//
// If this returns true, the user must call upb_EpsCopyInputStream_IsError()
// to distinguish between EOF and error.
UPB_INLINE bool upb_EpsCopyInputStream_IsDone(upb_EpsCopyInputStream* e,
                                              const char** ptr) {
  return upb_EpsCopyInputStream_IsDoneWithCallback(
      e, ptr, _upb_EpsCopyInputStream_IsDoneFallbackNoCallback);
}

// Returns the total number of bytes that are safe to read from the current
// buffer without reading uninitialized or unallocated memory.
//
// Note that this check does not respect any semantic limits on the stream,
// either limits from PushLimit() or the overall stream end, so some of these
// bytes may have unpredictable, nonsense values in them. The guarantee is only
// that the bytes are valid to read from the perspective of the C language
// (ie. you can read without triggering UBSAN or ASAN).
UPB_INLINE size_t upb_EpsCopyInputStream_BytesAvailable(
    upb_EpsCopyInputStream* e, const char* ptr) {
  return (e->end - ptr) + kSlopBytes;
}

// Returns true if the given delimited field size is valid (it does not extend
// beyond any previously-pushed limits).  `ptr` should point to the beginning
// of the field data, after the delimited size.
//
// Note that this does *not* guarantee that all of the data for this field is in
// the current buffer.
UPB_INLINE bool upb_EpsCopyInputStream_CheckSize(
    const upb_EpsCopyInputStream* e, const char* ptr, int size) {
  UPB_ASSERT(size >= 0);
  fprintf(stderr, "EpsStream_CheckSize(size=%d), ptr - e->end = %d, limit=%d\n",
          size, (int)(ptr - e->end), e->limit);
  return ptr - e->end + size <= e->limit;
}

UPB_INLINE bool _upb_EpsCopyInputStream_CheckSizeAvailable(
    upb_EpsCopyInputStream* e, const char* ptr, int size, bool submessage) {
  // This is one extra branch compared to the more normal:
  //   return (size_t)(end - ptr) < size;
  // However it is one less computation if we are just about to use "ptr + len":
  //   https://godbolt.org/z/35YGPz
  // In microbenchmarks this shows a small improvement.
  uintptr_t uptr = (uintptr_t)ptr;
  uintptr_t uend = (uintptr_t)e->limit_ptr;
  uintptr_t res = uptr + (size_t)size;
  if (!submessage) uend += kSlopBytes;
  // NOTE: this check depends on having a linear address space.  This is not
  // technically guaranteed by uintptr_t.
  bool ret = res >= uptr && res <= uend;
  if (size < 0) UPB_ASSERT(!ret);
  return ret;
}

// Returns true if the given delimited field size is valid (it does not extend
// beyond any previously-pushed limited) *and* all of the data for this field is
// available to be read in the current buffer.
//
// If the size is negative, this function will always return false. This
// property can be useful in some cases.
UPB_INLINE bool upb_EpsCopyInputStream_CheckDataSizeAvailable(
    upb_EpsCopyInputStream* e, const char* ptr, int size) {
  return _upb_EpsCopyInputStream_CheckSizeAvailable(e, ptr, size, false);
}

// Returns true if the given sub-message size is valid (it does not extend
// beyond any previously-pushed limited) *and* all of the data for this
// sub-message is available to be parsed in the current buffer.
//
// This implies that all fields from the sub-message can be parsed from the
// current buffer while maintaining the invariant that we always have at least
// kSlopBytes of data available past the beginning of
// any individual field start.
//
// If the size is negative, this function will always return false. This
// property can be useful in some cases.
UPB_INLINE bool upb_EpsCopyInputStream_CheckSubMessageSizeAvailable(
    upb_EpsCopyInputStream* e, const char* ptr, int size) {
  return _upb_EpsCopyInputStream_CheckSizeAvailable(e, ptr, size, true);
}

// Returns true if aliasing_enabled=true was passed to
// upb_EpsCopyInputStream_Init() when this stream was initialized.
UPB_INLINE bool upb_EpsCopyInputStream_AliasingEnabled(
    upb_EpsCopyInputStream* e) {
  return e->enable_aliasing;
}

// Returns true if aliasing_enabled=true was passed to
// upb_EpsCopyInputStream_Init() when this stream was initialized *and* we can
// alias into the region [ptr, size] in an input buffer.
UPB_INLINE bool upb_EpsCopyInputStream_AliasingAvailable(
    upb_EpsCopyInputStream* e, const char* ptr, size_t size) {
  // When EpsCopyInputStream supports streaming, this will need to become a
  // runtime check.
  return upb_EpsCopyInputStream_CheckDataSizeAvailable(e, ptr, size) &&
         e->enable_aliasing &&
         e->aliasing_delta != kUpb_EpsCopyInputStream_CannotAlias;
}

// Returns a pointer into an input buffer that corresponds to the parsing
// pointer `ptr`.  The returned pointer may be the same as `ptr`, but also may
// be different if we are currently parsing out of the patch buffer.
//
// REQUIRES: Aliasing must be available for the given pointer. If the input is a
// flat buffer and aliasing is enabled, then aliasing will always be available.
UPB_INLINE const char* upb_EpsCopyInputStream_GetAliasedPtr(
    upb_EpsCopyInputStream* e, const char* ptr) {
  UPB_ASSUME(upb_EpsCopyInputStream_AliasingAvailable(e, ptr, 0));
  uintptr_t delta =
      e->aliasing == kUpb_EpsCopyInputStream_NoDelta ? 0 : e->aliasing;
  return (const char*)((uintptr_t)ptr + delta);
}

// Reads string data from the input, aliasing into the input buffer instead of
// copying. The parsing pointer is passed in `*ptr`, and will be updated if
// necessary to point to the actual input buffer. Returns the new parsing
// pointer, which will be advanced past the string data.
//
// REQUIRES: Aliasing must be available for this data region (test with
// upb_EpsCopyInputStream_AliasingAvailable().
UPB_INLINE const char* upb_EpsCopyInputStream_ReadStringAliased(
    upb_EpsCopyInputStream* e, const char** ptr, size_t size) {
  UPB_ASSUME(upb_EpsCopyInputStream_AliasingAvailable(e, *ptr, size));
  const char* ret = *ptr + size;
  *ptr = (const char*)((uintptr_t)*ptr + delta);
  UPB_ASSUME(ret != NULL);
  return ret;
}

// Skips `size` bytes of string data from the input and returns a pointer past
// the end.  Returns NULL on end of stream or error.
UPB_INLINE const char* upb_EpsCopyInputStream_Skip(upb_EpsCopyInputStream* e,
                                                   const char* ptr, int size) {
  if (!upb_EpsCopyInputStream_CheckDataSizeAvailable(e, ptr, size)) return NULL;
  return ptr + size;
}

// Reads string data from the stream and advances the pointer accordingly.
// If aliasing was enabled when the stream was initialized, then the returned
// pointer will point into the input buffer if possible, otherwise new data
// will be allocated from arena and copied into. We may be forced to copy even
// if aliasing was enabled if the input data spans input buffers.
//
// Returns NULL if memory allocation failed, or we reached a premature EOF.
UPB_INLINE const char* upb_EpsCopyInputStream_ReadString(
    upb_EpsCopyInputStream* e, const char** ptr, size_t size,
    upb_Arena* arena) {
  if (upb_EpsCopyInputStream_AliasingAvailable(e, *ptr, size)) {
    return upb_EpsCopyInputStream_ReadStringAliased(e, ptr, size);
  } else {
    // We need to allocate and copy.
    if (!upb_EpsCopyInputStream_CheckDataSizeAvailable(e, *ptr, size)) {
      return NULL;
    }
    UPB_ASSERT(arena);
    char* data = (char*)upb_Arena_Malloc(arena, size);
    if (!data) return NULL;
    memcpy(data, *ptr, size);
    const char* ret = *ptr + size;
    *ptr = data;
    UPB_ASSUME(ret != NULL);
    return ret;
  }
}

// Pushes a limit onto the stack of limits for the current stream.  The limit
// will extend for `size` bytes beyond the position in `ptr`.  Future calls to
// upb_EpsCopyInputStream_IsDone() will return `true` when the stream position
// reaches this limit.
//
// Returns a delta that the caller must store and supply to PopLimit() below.
UPB_INLINE int upb_EpsCopyInputStream_PushLimit(upb_EpsCopyInputStream* e,
                                                const char* ptr, int size) {
  int limit = size + (int)(ptr - e->end);
  int delta = e->limit - limit;
  _upb_EpsCopyInputStream_CheckLimit(e);
  e->limit = limit;
  e->limit_ptr = e->end + UPB_MIN(0, limit);
  _upb_EpsCopyInputStream_CheckLimit(e);
  return delta;
}

// Pops the last limit that was pushed on this stream.  This may only be called
// once IsDone() returns true.  The user must pass the delta that was returned
// from PushLimit().
UPB_INLINE void upb_EpsCopyInputStream_PopLimit(upb_EpsCopyInputStream* e,
                                                const char* ptr,
                                                int saved_delta) {
  UPB_ASSERT(ptr - e->end == e->limit);
  _upb_EpsCopyInputStream_CheckLimit(e);
  e->limit += saved_delta;
  e->limit_ptr = e->end + UPB_MIN(0, e->limit);
  _upb_EpsCopyInputStream_CheckLimit(e);
}

typedef const char* upb_EpsCopyInputStream_ParseDelimitedFunc(
    upb_EpsCopyInputStream* e, const char* ptr, void* ctx);

// Tries to perform a fast-path handling of the given delimited message data.
// If the sub-message beginning at `*ptr` and extending for `len` is short and
// fits within this buffer, calls `func` with `ctx` as a parameter, where the
// pushing and popping of limits is handled automatically and with lower cost
// than the normal PushLimit()/PopLimit() sequence.
UPB_FORCEINLINE bool upb_EpsCopyInputStream_TryParseDelimitedFast(
    upb_EpsCopyInputStream* e, const char** ptr, int len,
    upb_EpsCopyInputStream_ParseDelimitedFunc* func, void* ctx) {
  if (!upb_EpsCopyInputStream_CheckSubMessageSizeAvailable(e, *ptr, len)) {
    return false;
  }

  // Fast case: Sub-message is <128 bytes and fits in the current buffer.
  // This means we can preserve limit/limit_ptr verbatim.
  const char* saved_limit_ptr = e->limit_ptr;
  int saved_limit = e->limit;
  e->limit_ptr = *ptr + len;
  e->limit = e->limit_ptr - e->end;
  UPB_ASSERT(e->limit_ptr == e->end + UPB_MIN(0, e->limit));
  *ptr = func(e, *ptr, ctx);
  e->limit_ptr = saved_limit_ptr;
  e->limit = saved_limit;
  UPB_ASSERT(e->limit_ptr == e->end + UPB_MIN(0, e->limit));
  return true;
}

#ifdef __cplusplus
} /* extern "C" */
#endif

#undef kSlopBytes

#include "upb/port/undef.inc"

#endif  // UPB_WIRE_EPS_COPY_INPUT_STREAM_H_
