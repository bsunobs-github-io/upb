#include "upb/wire/eps_copy_input_stream.h"

#include <string.h>

#include <cstdio>
#include <string>

#include "gtest/gtest.h"
#include "upb/upb.hpp"
// begin:google_only
// #include "testing/fuzzing/fuzztest.h"
// #include "upb/io/zero_copy_input_stream.h"
// end:google_only

// Must be last
#include "upb/port/def.inc"

namespace {

TEST(EpsCopyInputStreamTest, ZeroSize) {
  upb_EpsCopyInputStream stream;
  const char* ptr = NULL;
  ptr = upb_EpsCopyInputStream_Init(&stream, ptr, 0, NULL, false);
  EXPECT_TRUE(upb_EpsCopyInputStream_IsDone(&stream, &ptr));
}

// begin:google_only
//
// // We create a simple, trivial implementation of the stream that we can test
// // our real implementation against.
//
// class FakeStream {
//  public:
//   FakeStream(const std::string& data, bool stream)
//       : data_(data), offset_(0), stream_(stream) {
//     fprintf(stderr, "FakeStream stream=%d\n", (int)stream);
//     limits_.push_back(data.size());
//   }
//
//   // If we reached one or more limits correctly, returns the number of limits
//   // ended.  If we tried to read beyond the current limit, returns -1.
//   // Otherwise, for simple success, returns 0.
//   int ReadData(int n, std::string* data) {
//     if (n > BytesUntilLimit(false)) return -1;
//
//     data->assign(data_.data() + offset_, n);
//     offset_ += n;
//
//     int end_limit_count = 0;
//
//     while (BytesUntilLimit(false) == 0) {
//       if (PopLimit()) {
//         end_limit_count++;
//       } else {
//         eof_ = true;
//         break;
//       }
//     }
//
//     return end_limit_count;
//   }
//
//   bool TryPushLimit(int limit) {
//     if (!CheckSize(limit, true)) return false;
//     limits_.push_back(offset_ + limit);
//     return true;
//   }
//
//   bool IsEof() const { return eof_; }
//
//  private:
//   int BytesUntilLimit(bool fogged) const {
//     if (limits_.size() == 1 && fogged && stream_ &&
//         offset_ < limits_[0] - kUpb_EpsCopyInputStream_SlopBytes) {
//       return INT_MAX - offset_;
//     }
//     return limits_.back() - offset_;
//   }
//
//   bool CheckSize(int size, bool fogged) const {
//     fprintf(stderr, "FakeStream::BytesUntilLimit()=%d, offset=%d\n",
//             BytesUntilLimit(fogged), offset_);
//     return BytesUntilLimit(fogged) >= size;
//   }
//
//   // Return false on EOF.
//   bool PopLimit() {
//     limits_.pop_back();
//     return !limits_.empty();
//   }
//
//   std::string data_;
//   // Limits, specified in absolute stream terms.
//   std::vector<int> limits_;
//   int offset_;
//   // When we are streaming, we do not have visibility into the end-of-stream
//   // limit until we are within kSlopBytes of it.
//   bool stream_;
//   bool eof_ = false;
// };
//
// char tmp_buf[kUpb_EpsCopyInputStream_SlopBytes];
//
// // This class is like a std::string, except we can "delete" bytes from the
// // beginning of a string when they should no longer be accessible, without
// // moving or invalidating the remaining bytes.  We can't actually delete the
// // front bytes, but we can poison them to make them behave as though they are
// // deleted when used with ASAN.  This will help verify that our streaming
// // abstractions are not accessing bytes after they should no longer be
// // accessible.
// class StreamingString {
//  public:
//   StreamingString(absl::string_view data) : data_(data) {}
//
//   ~StreamingString() {
//     UPB_UNPOISON_MEMORY_REGION(data_.data(), poison_offset_);
//   }
//
//   void DeleteFront(size_t bytes) {
//     UPB_POISON_MEMORY_REGION(data_.data() + poison_offset_, bytes);
//     poison_offset_ += bytes;
//   }
//
//   char* data() { return data_.data() + poison_offset_; }
//   const char* data() const { return data_.data() + poison_offset_; }
//   size_t size() const { return data_.size() - poison_offset_; }
//
//  private:
//   std::string data_;
//   size_t poison_offset_ = 0;
// };
//
// // A upb_ZeroCopyInputStream that vends a data buffer split into several
// // sub-buffers. Used to test that consumers can handle buffer seams in arbitrary
// // places.
// class SeamStream : public upb_ZeroCopyInputStream {
//  public:
//   SeamStream(const std::string& data, const std::vector<int>& chunks) {
//     CHECK(!chunks.empty());
//     int ofs = chunks[0];
//     for (int i = 1; i < chunks.size(); ++i) {
//       int chunk = chunks[i];
//       if (data.size() - ofs < chunk) break;
//       data_.push_back(absl::string_view(data.substr(ofs, chunk)));
//       ofs += chunk;
//     }
//     if (ofs < data.size()) data_.push_back(absl::string_view(data.substr(ofs)));
//     for (const auto chunk : data_) {
//       fprintf(stderr, "- SeamStream chunk size=%zu, data=%s\n", chunk.size(),
//               chunk.data());
//     }
//     this->vtable = &static_vtable;
//   }
//
//   int LastChunkSize() const { return data_.back().size(); }
//
//   static const void* Next(upb_ZeroCopyInputStream* z, size_t* count,
//                           upb_Status* status) {
//     SeamStream* s = reinterpret_cast<SeamStream*>(z);
//     if (!s->again_) s->data_.pop_front();
//     if (s->data_.empty()) {
//       *count = 0;
//       return NULL;
//     }
//     s->again_ = false;
//     s->position_ += s->data_.front().size();
//     *count = s->data_.front().size();
//     return s->data_.front().data();
//   }
//
//   static void BackUp(upb_ZeroCopyInputStream* z, size_t count) {
//     SeamStream* s = reinterpret_cast<SeamStream*>(z);
//     CHECK(!s->again_);  // Can't back up twice in a row.
//     CHECK(s->data_.front().size() >= count);
//
//     // This will prevent access to anything behind the back up point. This may
//     // be a bit more strict than what ZeroCopyInputStream specifies in its
//     // contract, but generally we want our decoders to respect this rule.
//     s->data_.front().DeleteFront(s->data_.front().size() - count);
//
//     s->again_ = true;
//     s->position_ -= count;
//   }
//
//   static bool Skip(upb_ZeroCopyInputStream* z, size_t count) {
//     SeamStream* s = reinterpret_cast<SeamStream*>(z);
//     while (count && !s->data_.empty()) {
//       if (count < s->data_.front().size()) break;
//       count -= s->data_.front().size();
//       s->data_.pop_front();
//     }
//     if (count) {
//       if (s->data_.empty()) return false;
//       s->data_.front().DeleteFront(count);
//     }
//     s->position_ += count;
//     return true;
//   }
//
//   static size_t ByteCount(const upb_ZeroCopyInputStream* z) {
//     const SeamStream* s = reinterpret_cast<const SeamStream*>(z);
//     return s->position_;
//   }
//
//  private:
//   std::deque<StreamingString> data_;
//   bool again_ = true;
//   size_t position_ = 0;
//   static _upb_ZeroCopyInputStream_VTable static_vtable;
// };
//
// _upb_ZeroCopyInputStream_VTable SeamStream::static_vtable = {
//     &SeamStream::Next, &SeamStream::BackUp, &SeamStream::Skip,
//     &SeamStream::ByteCount};
//
// class EpsStream {
//  public:
//   EpsStream(const std::string& data, const std::vector<int>& chunks,
//             bool enable_aliasing)
//       : total_size_(data.size()), enable_aliasing_(enable_aliasing) {
//     size_t flat_data_size = data.size();
//     if (!chunks.empty() && chunks[0] < flat_data_size) {
//       flat_data_size = std::min<size_t>(flat_data_size, chunks[0]);
//       fprintf(stderr, "EpsStream flat_data_.size()=%zu, data=%.*s\n",
//               flat_data_size, (int)flat_data_size, data.data());
//       seam_stream_ = std::make_unique<SeamStream>(data, chunks);
//     } else {
//       fprintf(stderr, "EpsStream data is totally flat, size=%zu\n",
//               flat_data_size);
//     }
//     flat_data_.assign(data.data(), flat_data_size);
//     ptr_ = flat_data_.data();
//     ptr_ = upb_EpsCopyInputStream_Init(&eps_, ptr_, flat_data_.size(),
//                                        seam_stream_.get(), enable_aliasing);
//   }
//
//   bool streaming() const { return seam_stream_.get() != nullptr; }
//
//   // Returns false at EOF or error.
//   int ReadData(int n, std::string* data) {
//     fprintf(stderr, "ReadData n=%d\n", n);
//     EXPECT_LE(n, kUpb_EpsCopyInputStream_SlopBytes);
//     if (enable_aliasing_) {
//       EXPECT_TRUE(upb_EpsCopyInputStream_AliasingAvailable(&eps_, ptr_, n));
//     }
//     // We want to verify that we can read kUpb_EpsCopyInputStream_SlopBytes
//     // safely, even if we haven't actually been requested to read that much.
//     // We copy to a global buffer so the copy can't be optimized away.
//     memcpy(&tmp_buf, ptr_, kUpb_EpsCopyInputStream_SlopBytes);
//     data->assign(tmp_buf, n);
//     ptr_ += n;
//     if (enable_aliasing_) {
//       EXPECT_TRUE(upb_EpsCopyInputStream_AliasingAvailable(&eps_, ptr_, 0));
//     }
//     return PopLimits();
//   }
//
//   int ReadString(int n, std::string* data) {
//     if (!upb_EpsCopyInputStream_CheckSize(&eps_, ptr_, n)) return -1;
//     const char* str_data = ptr_;
//     if (enable_aliasing_) {
//       EXPECT_TRUE(upb_EpsCopyInputStream_AliasingAvailable(&eps_, ptr_, n));
//     }
//     ptr_ = upb_EpsCopyInputStream_ReadString(&eps_, &str_data, n, arena_.ptr());
//     if (!ptr_) return -1;
//     if (!seam_stream_ && enable_aliasing_ && n) {
//       EXPECT_GE(reinterpret_cast<uintptr_t>(str_data),
//                 reinterpret_cast<uintptr_t>(flat_data_.data()));
//       EXPECT_LT(
//           reinterpret_cast<uintptr_t>(str_data),
//           reinterpret_cast<uintptr_t>(flat_data_.data() + flat_data_.size()));
//       EXPECT_TRUE(upb_EpsCopyInputStream_AliasingAvailable(&eps_, ptr_, 0));
//     }
//     data->assign(str_data, n);
//     return PopLimits();
//   }
//
//   bool TryPushLimit(int limit) {
//     fprintf(stderr, "TryPushLimit, limit=%d\n", limit);
//     if (!upb_EpsCopyInputStream_CheckSize(&eps_, ptr_, limit)) return false;
//     deltas_.push_back(upb_EpsCopyInputStream_PushLimit(&eps_, ptr_, limit));
//     return true;
//   }
//
//   bool IsEof() const { return eof_; }
//
//  private:
//   int PopLimits() {
//     int end_limit_count = 0;
//
//     while (IsAtLimit()) {
//       if (IsError()) return -1;
//       if (PopLimit()) {
//         end_limit_count++;
//       } else {
//         eof_ = true;  // EOF.
//         break;
//       }
//     }
//
//     return IsError() ? -1 : end_limit_count;
//   }
//
//   bool IsAtLimit() {
//     bool ret = upb_EpsCopyInputStream_IsDoneWithCallback(
//         &eps_, &ptr_, &EpsStream::IsDoneFallback);
//     fprintf(stderr, "IsAtLimit=%d\n", (int)ret);
//     return ret;
//   }
//
//   bool IsError() const {
//     EXPECT_EQ(error_, eps_.error);
//     fprintf(stderr, "IsError=%d\n", (int)error_);
//     return error_;
//   }
//
//   // Return false on EOF.
//   bool PopLimit() {
//     if (deltas_.empty()) return false;
//     upb_EpsCopyInputStream_PopLimit(&eps_, ptr_, deltas_.back());
//     deltas_.pop_back();
//     return true;
//   }
//
//   static const char* IsDoneFallback(upb_EpsCopyInputStream* e, const char* ptr,
//                                     int overrun) {
//     fprintf(stderr, "IsDoneFallback, overrun=%d\n", overrun);
//     return _upb_EpsCopyInputStream_IsDoneFallbackInline(
//         e, ptr, overrun, &EpsStream::BufferFlipCallback);
//   }
//
//   static const char* BufferFlipCallback(upb_EpsCopyInputStream* e,
//                                         const char* old_end,
//                                         const char* new_start) {
//     EpsStream* stream = reinterpret_cast<EpsStream*>(e);
//     if (!old_end) stream->error_ = true;
//     return new_start;
//   }
//
//   upb_EpsCopyInputStream eps_;
//   int total_size_;
//   std::string flat_data_;
//   std::unique_ptr<SeamStream> seam_stream_;
//   const char* ptr_;
//   std::vector<int> deltas_;
//   upb::Arena arena_;
//   bool error_ = false;
//   bool eof_ = false;
//   bool enable_aliasing_;
// };
//
// // Reads N bytes from the given position.
// struct ReadOp {
//   int bytes;  // Must be <= kUpb_EpsCopyInputStream_SlopBytes.
// };
//
// struct ReadStringOp {
//   int bytes;
// };
//
// // Pushes a new limit of N bytes from the current position.
// struct PushLimitOp {
//   int bytes;
// };
//
// typedef std::variant<ReadOp, ReadStringOp, PushLimitOp> Op;
//
// struct EpsCopyTestScript {
//   int data_size;
//   bool enable_aliasing;
//   std::vector<Op> ops;
//   std::vector<int> chunks;
// };
//
// auto ArbitraryEpsCopyTestScript() {
//   using ::fuzztest::Arbitrary;
//   using ::fuzztest::InRange;
//   using ::fuzztest::NonNegative;
//   using ::fuzztest::StructOf;
//   using ::fuzztest::VariantOf;
//   using ::fuzztest::VectorOf;
//
//   int max_data_size = 512;
//
//   return StructOf<EpsCopyTestScript>(
//       InRange(0, max_data_size),  // data_size
//       Arbitrary<bool>(),          // enable_aliasing
//       VectorOf(VariantOf(
//           // ReadOp
//           StructOf<ReadOp>(InRange(1, kUpb_EpsCopyInputStream_SlopBytes)),
//           // ReadStringOp
//           StructOf<ReadStringOp>(NonNegative<int>()),
//           // PushLimitOp
//           StructOf<PushLimitOp>(NonNegative<int>()))),
//       VectorOf(InRange(1, max_data_size)));
// }
//
// // Run a test that creates both real stream and a fake stream, and validates
// // that they have the same behavior.
// void TestAgainstFakeStream(const EpsCopyTestScript& script) {
//   std::string data(script.data_size, 'x');
//   std::string printable_chars;
//   for (char ch = 'A'; ch <= 'Z'; ++ch) printable_chars += ch;
//   for (char ch = 'a'; ch <= 'z'; ++ch) printable_chars += ch;
//   for (char ch = '0'; ch <= '9'; ++ch) printable_chars += ch;
//   int char_idx = 0;
//   for (int i = 0; i < script.data_size; ++i) {
//     // Avoid putting any zeroes in the buffer.
//     data[i] = printable_chars[char_idx++];
//     if (char_idx == printable_chars.size()) char_idx = 0;
//   }
//
//   EpsStream eps_stream(data, script.chunks, script.enable_aliasing);
//   FakeStream fake_stream(data, eps_stream.streaming());
//
//   for (const auto& op : script.ops) {
//     if (const ReadOp* read_op = std::get_if<ReadOp>(&op)) {
//       std::string data_fake;
//       std::string data_eps;
//       int fake_result = fake_stream.ReadData(read_op->bytes, &data_fake);
//       int eps_result = eps_stream.ReadData(read_op->bytes, &data_eps);
//       EXPECT_EQ(fake_result, eps_result);
//       if (fake_result == -1) break;  // Error
//       EXPECT_EQ(data_fake, data_eps);
//       EXPECT_EQ(fake_stream.IsEof(), eps_stream.IsEof());
//       if (fake_stream.IsEof()) break;
//     } else if (const ReadStringOp* read_op = std::get_if<ReadStringOp>(&op)) {
//       std::string data_fake;
//       std::string data_eps;
//       int fake_result = fake_stream.ReadData(read_op->bytes, &data_fake);
//       int eps_result = eps_stream.ReadString(read_op->bytes, &data_eps);
//       EXPECT_EQ(fake_result, eps_result);
//       if (fake_result == -1) break;  // Error
//       EXPECT_EQ(data_fake, data_eps);
//       EXPECT_EQ(fake_stream.IsEof(), eps_stream.IsEof());
//       if (fake_stream.IsEof()) break;
//     } else if (const PushLimitOp* push = std::get_if<PushLimitOp>(&op)) {
//       EXPECT_EQ(fake_stream.TryPushLimit(push->bytes),
//                 eps_stream.TryPushLimit(push->bytes));
//     } else {
//       EXPECT_TRUE(false);  // Unknown op.
//     }
//   }
// }
//
// // Test with:
// //  $ blaze run --config=fuzztest third_party/upb:eps_copy_input_stream_test \
// //   -- --gunit_fuzz=
// FUZZ_TEST(EpsCopyFuzzTest, TestAgainstFakeStream)
//     .WithDomains(ArbitraryEpsCopyTestScript());
//
// TEST(EpsCopyFuzzTest, TestAgainstFakeStreamRegression) {
//   TestAgainstFakeStream({299,
//                          false,
//                          {
//                              PushLimitOp{2},
//                              ReadOp{14},
//                          }});
// }
//
// TEST(EpsCopyFuzzTest, AliasingEnabledZeroSizeReadString) {
//   TestAgainstFakeStream({510, true, {ReadStringOp{0}}});
// }
//
// TEST(EpsCopyFuzzTest, AliasingDisabledZeroSizeReadString) {
//   TestAgainstFakeStream({510, false, {ReadStringOp{0}}});
// }
//
// TEST(EpsCopyFuzzTest, ReadStringZero) {
//   TestAgainstFakeStream({0, true, {ReadStringOp{0}}});
// }
//
// TEST(EpsCopyFuzzTest, ReadZero) {
//   TestAgainstFakeStream({0, true, {ReadOp{0}}});
// }
//
// TEST(EpsCopyFuzzTest, ReadZeroTwice) {
//   TestAgainstFakeStream({0, true, {ReadOp{0}, ReadOp{0}}});
// }
//
// TEST(EpsCopyFuzzTest, ReadStringZeroThenRead) {
//   TestAgainstFakeStream({0, true, {ReadStringOp{0}, ReadOp{0}}});
// }
//
// TEST(EpsCopyFuzzTest, ReadStringOverflowsBufferButNotLimit) {
//   TestAgainstFakeStream({351,
//                          false,
//                          {
//                              ReadOp{7},
//                              PushLimitOp{2147483647},
//                              ReadStringOp{344},
//                          }});
// }
//
// TEST(EpsCopyFuzzTest, LastBufferAliasing) {
//   TestAgainstFakeStream({27, true, {ReadOp{12}, ReadStringOp{3}}});
// }
//
// TEST(EpsCopyFuzzTest, FirstBufferAliasing) {
//   TestAgainstFakeStream({7, true, {ReadStringOp{3}}});
// }
//
// TEST(EpsCopyFuzzTest, SmallFirstBufferInStream) {
//   TestAgainstFakeStream({32, false, {ReadOp{8}}, {1}});
// }
//
// TEST(EpsCopyFuzzTest, ManyShort) {
//   TestAgainstFakeStream({32,
//                          true,
//                          {
//                              ReadOp{1},
//                          },
//                          {1, 1}});
// }
//
// TEST(EpsCopyFuzzTest, ManyShort2) {
//   TestAgainstFakeStream({181,
//                          false,
//                          {ReadOp{1}, ReadOp{13}, ReadStringOp{0}},
//                          {1, 1, 1, 1, 9, 1}});
// }
//
// TEST(EpsCopyFuzzTest, HugeLimit) {
//   TestAgainstFakeStream({64, false, {PushLimitOp{884509199}}, {1}});
// }
//
// TEST(EpsCopyFuzzTest, HugeLimit2) {
//   TestAgainstFakeStream({16, false, {PushLimitOp{884509199}}, {1, 1, 1, 161}});
// }
//
// TEST(EpsCopyFuzzTest, HugeLimit3) {
//   TestAgainstFakeStream(
//       {129, true, {ReadOp{1}, PushLimitOp{2147483647}}, {1, 1, 1, 20, 307}});
// }
//
// TEST(EpsCopyFuzzTest, OversizeReadString) {
//   TestAgainstFakeStream({278,
//                          false,
//                          {ReadStringOp{0}, ReadOp{16}, ReadOp{1}, ReadOp{10},
//                           ReadOp{16}, ReadOp{12}, ReadStringOp{1349638079}},
//                          {2, 70, 316, 39, 1, 1, 1, 375, 414}});
// }
//
// TEST(EpsCopyFuzzTest, LargeChunkSeenInFallback) {
//   TestAgainstFakeStream({18, false, {ReadOp{16}}, {1, 1, 16}});
// }
//
// TEST(EpsCopyFuzzTest, Foo) {
//   TestAgainstFakeStream({319, true, {PushLimitOp{2147483647}}, {159, 160}});
// }
//
// end:google_only

}  // namespace
