/* This file was generated by upbc (the upb compiler) from the input
 * file:
 *
 *     google/protobuf/descriptor.proto
 *
 * Do not edit -- your changes will be discarded when the file is
 * regenerated. */

#include <stddef.h>
#include "upb/internal/array.h"
#include "upb/msg_internal.h"
#include "google/protobuf/descriptor.upb.h"

#include "upb/port_def.inc"

static const upb_MiniTable_Sub google_protobuf_FileDescriptorSet_submsgs[1] = {
  {.submsg = &google_protobuf_FileDescriptorProto_msg_init},
};

static const upb_MiniTable_Field google_protobuf_FileDescriptorSet__fields[1] = {
  {1, UPB_SIZE(0, 0), UPB_SIZE(0, 0), 0, 11, kUpb_FieldMode_Array | (UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google_protobuf_FileDescriptorSet_msg_init = {
  &google_protobuf_FileDescriptorSet_submsgs[0],
  &google_protobuf_FileDescriptorSet__fields[0],
  UPB_SIZE(8, 8), 1, kUpb_ExtMode_NonExtendable, 1, 255, 0,
};

static const upb_MiniTable_Sub google_protobuf_FileDescriptorProto_submsgs[6] = {
  {.submsg = &google_protobuf_DescriptorProto_msg_init},
  {.submsg = &google_protobuf_EnumDescriptorProto_msg_init},
  {.submsg = &google_protobuf_ServiceDescriptorProto_msg_init},
  {.submsg = &google_protobuf_FieldDescriptorProto_msg_init},
  {.submsg = &google_protobuf_FileOptions_msg_init},
  {.submsg = &google_protobuf_SourceCodeInfo_msg_init},
};

static const upb_MiniTable_Field google_protobuf_FileDescriptorProto__fields[13] = {
  {1, UPB_SIZE(40, 8), UPB_SIZE(1, 1), kUpb_NoSub, 12, kUpb_FieldMode_Scalar | kUpb_LabelFlags_IsAlternate | (kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(48, 24), UPB_SIZE(2, 2), kUpb_NoSub, 12, kUpb_FieldMode_Scalar | kUpb_LabelFlags_IsAlternate | (kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(4, 40), UPB_SIZE(0, 0), kUpb_NoSub, 12, kUpb_FieldMode_Array | kUpb_LabelFlags_IsAlternate | (UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(8, 48), UPB_SIZE(0, 0), 0, 11, kUpb_FieldMode_Array | (UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(12, 56), UPB_SIZE(0, 0), 1, 11, kUpb_FieldMode_Array | (UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(16, 64), UPB_SIZE(0, 0), 2, 11, kUpb_FieldMode_Array | (UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(20, 72), UPB_SIZE(0, 0), 3, 11, kUpb_FieldMode_Array | (UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {8, UPB_SIZE(24, 80), UPB_SIZE(3, 3), 4, 11, kUpb_FieldMode_Scalar | (UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {9, UPB_SIZE(28, 88), UPB_SIZE(4, 4), 5, 11, kUpb_FieldMode_Scalar | (UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {10, UPB_SIZE(32, 96), UPB_SIZE(0, 0), kUpb_NoSub, 5, kUpb_FieldMode_Array | (UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {11, UPB_SIZE(36, 104), UPB_SIZE(0, 0), kUpb_NoSub, 5, kUpb_FieldMode_Array | (UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {12, UPB_SIZE(56, 112), UPB_SIZE(5, 5), kUpb_NoSub, 12, kUpb_FieldMode_Scalar | kUpb_LabelFlags_IsAlternate | (kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {13, UPB_SIZE(64, 128), UPB_SIZE(6, 6), kUpb_NoSub, 12, kUpb_FieldMode_Scalar | kUpb_LabelFlags_IsAlternate | (kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google_protobuf_FileDescriptorProto_msg_init = {
  &google_protobuf_FileDescriptorProto_submsgs[0],
  &google_protobuf_FileDescriptorProto__fields[0],
  UPB_SIZE(72, 144), 13, kUpb_ExtMode_NonExtendable, 13, 255, 0,
};

static const upb_MiniTable_Sub google_protobuf_DescriptorProto_submsgs[8] = {
  {.submsg = &google_protobuf_FieldDescriptorProto_msg_init},
  {.submsg = &google_protobuf_DescriptorProto_msg_init},
  {.submsg = &google_protobuf_EnumDescriptorProto_msg_init},
  {.submsg = &google_protobuf_DescriptorProto_ExtensionRange_msg_init},
  {.submsg = &google_protobuf_FieldDescriptorProto_msg_init},
  {.submsg = &google_protobuf_MessageOptions_msg_init},
  {.submsg = &google_protobuf_OneofDescriptorProto_msg_init},
  {.submsg = &google_protobuf_DescriptorProto_ReservedRange_msg_init},
};

static const upb_MiniTable_Field google_protobuf_DescriptorProto__fields[10] = {
  {1, UPB_SIZE(40, 8), UPB_SIZE(1, 1), kUpb_NoSub, 12, kUpb_FieldMode_Scalar | kUpb_LabelFlags_IsAlternate | (kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(4, 24), UPB_SIZE(0, 0), 0, 11, kUpb_FieldMode_Array | (UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(8, 32), UPB_SIZE(0, 0), 1, 11, kUpb_FieldMode_Array | (UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(12, 40), UPB_SIZE(0, 0), 2, 11, kUpb_FieldMode_Array | (UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(16, 48), UPB_SIZE(0, 0), 3, 11, kUpb_FieldMode_Array | (UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(20, 56), UPB_SIZE(0, 0), 4, 11, kUpb_FieldMode_Array | (UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(24, 64), UPB_SIZE(2, 2), 5, 11, kUpb_FieldMode_Scalar | (UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {8, UPB_SIZE(28, 72), UPB_SIZE(0, 0), 6, 11, kUpb_FieldMode_Array | (UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {9, UPB_SIZE(32, 80), UPB_SIZE(0, 0), 7, 11, kUpb_FieldMode_Array | (UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {10, UPB_SIZE(36, 88), UPB_SIZE(0, 0), kUpb_NoSub, 12, kUpb_FieldMode_Array | kUpb_LabelFlags_IsAlternate | (UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google_protobuf_DescriptorProto_msg_init = {
  &google_protobuf_DescriptorProto_submsgs[0],
  &google_protobuf_DescriptorProto__fields[0],
  UPB_SIZE(48, 96), 10, kUpb_ExtMode_NonExtendable, 10, 255, 0,
};

static const upb_MiniTable_Sub google_protobuf_DescriptorProto_ExtensionRange_submsgs[1] = {
  {.submsg = &google_protobuf_ExtensionRangeOptions_msg_init},
};

static const upb_MiniTable_Field google_protobuf_DescriptorProto_ExtensionRange__fields[3] = {
  {1, UPB_SIZE(4, 4), UPB_SIZE(1, 1), kUpb_NoSub, 5, kUpb_FieldMode_Scalar | (kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(8, 8), UPB_SIZE(2, 2), kUpb_NoSub, 5, kUpb_FieldMode_Scalar | (kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(12, 16), UPB_SIZE(3, 3), 0, 11, kUpb_FieldMode_Scalar | (UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google_protobuf_DescriptorProto_ExtensionRange_msg_init = {
  &google_protobuf_DescriptorProto_ExtensionRange_submsgs[0],
  &google_protobuf_DescriptorProto_ExtensionRange__fields[0],
  UPB_SIZE(16, 24), 3, kUpb_ExtMode_NonExtendable, 3, 255, 0,
};

static const upb_MiniTable_Field google_protobuf_DescriptorProto_ReservedRange__fields[2] = {
  {1, UPB_SIZE(4, 4), UPB_SIZE(1, 1), kUpb_NoSub, 5, kUpb_FieldMode_Scalar | (kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(8, 8), UPB_SIZE(2, 2), kUpb_NoSub, 5, kUpb_FieldMode_Scalar | (kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google_protobuf_DescriptorProto_ReservedRange_msg_init = {
  NULL,
  &google_protobuf_DescriptorProto_ReservedRange__fields[0],
  UPB_SIZE(16, 16), 2, kUpb_ExtMode_NonExtendable, 2, 255, 0,
};

static const upb_MiniTable_Sub google_protobuf_ExtensionRangeOptions_submsgs[1] = {
  {.submsg = &google_protobuf_UninterpretedOption_msg_init},
};

static const upb_MiniTable_Field google_protobuf_ExtensionRangeOptions__fields[1] = {
  {999, UPB_SIZE(0, 0), UPB_SIZE(0, 0), 0, 11, kUpb_FieldMode_Array | (UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google_protobuf_ExtensionRangeOptions_msg_init = {
  &google_protobuf_ExtensionRangeOptions_submsgs[0],
  &google_protobuf_ExtensionRangeOptions__fields[0],
  UPB_SIZE(8, 8), 1, kUpb_ExtMode_Extendable, 0, 255, 0,
};

static const upb_MiniTable_Sub google_protobuf_FieldDescriptorProto_submsgs[3] = {
  {.subenum = &google_protobuf_FieldDescriptorProto_Label_enum_init},
  {.subenum = &google_protobuf_FieldDescriptorProto_Type_enum_init},
  {.submsg = &google_protobuf_FieldOptions_msg_init},
};

static const upb_MiniTable_Field google_protobuf_FieldDescriptorProto__fields[11] = {
  {1, UPB_SIZE(28, 24), UPB_SIZE(1, 1), kUpb_NoSub, 12, kUpb_FieldMode_Scalar | kUpb_LabelFlags_IsAlternate | (kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(36, 40), UPB_SIZE(2, 2), kUpb_NoSub, 12, kUpb_FieldMode_Scalar | kUpb_LabelFlags_IsAlternate | (kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(4, 4), UPB_SIZE(3, 3), kUpb_NoSub, 5, kUpb_FieldMode_Scalar | (kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(8, 8), UPB_SIZE(4, 4), 0, 14, kUpb_FieldMode_Scalar | (kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(12, 12), UPB_SIZE(5, 5), 1, 14, kUpb_FieldMode_Scalar | (kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(44, 56), UPB_SIZE(6, 6), kUpb_NoSub, 12, kUpb_FieldMode_Scalar | kUpb_LabelFlags_IsAlternate | (kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(52, 72), UPB_SIZE(7, 7), kUpb_NoSub, 12, kUpb_FieldMode_Scalar | kUpb_LabelFlags_IsAlternate | (kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {8, UPB_SIZE(16, 88), UPB_SIZE(8, 8), 2, 11, kUpb_FieldMode_Scalar | (UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {9, UPB_SIZE(20, 16), UPB_SIZE(9, 9), kUpb_NoSub, 5, kUpb_FieldMode_Scalar | (kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {10, UPB_SIZE(60, 96), UPB_SIZE(10, 10), kUpb_NoSub, 12, kUpb_FieldMode_Scalar | kUpb_LabelFlags_IsAlternate | (kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {17, UPB_SIZE(24, 20), UPB_SIZE(11, 11), kUpb_NoSub, 8, kUpb_FieldMode_Scalar | (kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google_protobuf_FieldDescriptorProto_msg_init = {
  &google_protobuf_FieldDescriptorProto_submsgs[0],
  &google_protobuf_FieldDescriptorProto__fields[0],
  UPB_SIZE(72, 112), 11, kUpb_ExtMode_NonExtendable, 10, 255, 0,
};

static const upb_MiniTable_Sub google_protobuf_OneofDescriptorProto_submsgs[1] = {
  {.submsg = &google_protobuf_OneofOptions_msg_init},
};

static const upb_MiniTable_Field google_protobuf_OneofDescriptorProto__fields[2] = {
  {1, UPB_SIZE(8, 8), UPB_SIZE(1, 1), kUpb_NoSub, 12, kUpb_FieldMode_Scalar | kUpb_LabelFlags_IsAlternate | (kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(4, 24), UPB_SIZE(2, 2), 0, 11, kUpb_FieldMode_Scalar | (UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google_protobuf_OneofDescriptorProto_msg_init = {
  &google_protobuf_OneofDescriptorProto_submsgs[0],
  &google_protobuf_OneofDescriptorProto__fields[0],
  UPB_SIZE(16, 32), 2, kUpb_ExtMode_NonExtendable, 2, 255, 0,
};

static const upb_MiniTable_Sub google_protobuf_EnumDescriptorProto_submsgs[3] = {
  {.submsg = &google_protobuf_EnumValueDescriptorProto_msg_init},
  {.submsg = &google_protobuf_EnumOptions_msg_init},
  {.submsg = &google_protobuf_EnumDescriptorProto_EnumReservedRange_msg_init},
};

static const upb_MiniTable_Field google_protobuf_EnumDescriptorProto__fields[5] = {
  {1, UPB_SIZE(20, 8), UPB_SIZE(1, 1), kUpb_NoSub, 12, kUpb_FieldMode_Scalar | kUpb_LabelFlags_IsAlternate | (kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(4, 24), UPB_SIZE(0, 0), 0, 11, kUpb_FieldMode_Array | (UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(8, 32), UPB_SIZE(2, 2), 1, 11, kUpb_FieldMode_Scalar | (UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(12, 40), UPB_SIZE(0, 0), 2, 11, kUpb_FieldMode_Array | (UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(16, 48), UPB_SIZE(0, 0), kUpb_NoSub, 12, kUpb_FieldMode_Array | kUpb_LabelFlags_IsAlternate | (UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google_protobuf_EnumDescriptorProto_msg_init = {
  &google_protobuf_EnumDescriptorProto_submsgs[0],
  &google_protobuf_EnumDescriptorProto__fields[0],
  UPB_SIZE(32, 56), 5, kUpb_ExtMode_NonExtendable, 5, 255, 0,
};

static const upb_MiniTable_Field google_protobuf_EnumDescriptorProto_EnumReservedRange__fields[2] = {
  {1, UPB_SIZE(4, 4), UPB_SIZE(1, 1), kUpb_NoSub, 5, kUpb_FieldMode_Scalar | (kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(8, 8), UPB_SIZE(2, 2), kUpb_NoSub, 5, kUpb_FieldMode_Scalar | (kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google_protobuf_EnumDescriptorProto_EnumReservedRange_msg_init = {
  NULL,
  &google_protobuf_EnumDescriptorProto_EnumReservedRange__fields[0],
  UPB_SIZE(16, 16), 2, kUpb_ExtMode_NonExtendable, 2, 255, 0,
};

static const upb_MiniTable_Sub google_protobuf_EnumValueDescriptorProto_submsgs[1] = {
  {.submsg = &google_protobuf_EnumValueOptions_msg_init},
};

static const upb_MiniTable_Field google_protobuf_EnumValueDescriptorProto__fields[3] = {
  {1, UPB_SIZE(12, 8), UPB_SIZE(1, 1), kUpb_NoSub, 12, kUpb_FieldMode_Scalar | kUpb_LabelFlags_IsAlternate | (kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(4, 4), UPB_SIZE(2, 2), kUpb_NoSub, 5, kUpb_FieldMode_Scalar | (kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(8, 24), UPB_SIZE(3, 3), 0, 11, kUpb_FieldMode_Scalar | (UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google_protobuf_EnumValueDescriptorProto_msg_init = {
  &google_protobuf_EnumValueDescriptorProto_submsgs[0],
  &google_protobuf_EnumValueDescriptorProto__fields[0],
  UPB_SIZE(24, 32), 3, kUpb_ExtMode_NonExtendable, 3, 255, 0,
};

static const upb_MiniTable_Sub google_protobuf_ServiceDescriptorProto_submsgs[2] = {
  {.submsg = &google_protobuf_MethodDescriptorProto_msg_init},
  {.submsg = &google_protobuf_ServiceOptions_msg_init},
};

static const upb_MiniTable_Field google_protobuf_ServiceDescriptorProto__fields[3] = {
  {1, UPB_SIZE(12, 8), UPB_SIZE(1, 1), kUpb_NoSub, 12, kUpb_FieldMode_Scalar | kUpb_LabelFlags_IsAlternate | (kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(4, 24), UPB_SIZE(0, 0), 0, 11, kUpb_FieldMode_Array | (UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(8, 32), UPB_SIZE(2, 2), 1, 11, kUpb_FieldMode_Scalar | (UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google_protobuf_ServiceDescriptorProto_msg_init = {
  &google_protobuf_ServiceDescriptorProto_submsgs[0],
  &google_protobuf_ServiceDescriptorProto__fields[0],
  UPB_SIZE(24, 40), 3, kUpb_ExtMode_NonExtendable, 3, 255, 0,
};

static const upb_MiniTable_Sub google_protobuf_MethodDescriptorProto_submsgs[1] = {
  {.submsg = &google_protobuf_MethodOptions_msg_init},
};

static const upb_MiniTable_Field google_protobuf_MethodDescriptorProto__fields[6] = {
  {1, UPB_SIZE(12, 8), UPB_SIZE(1, 1), kUpb_NoSub, 12, kUpb_FieldMode_Scalar | kUpb_LabelFlags_IsAlternate | (kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(20, 24), UPB_SIZE(2, 2), kUpb_NoSub, 12, kUpb_FieldMode_Scalar | kUpb_LabelFlags_IsAlternate | (kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(28, 40), UPB_SIZE(3, 3), kUpb_NoSub, 12, kUpb_FieldMode_Scalar | kUpb_LabelFlags_IsAlternate | (kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(4, 56), UPB_SIZE(4, 4), 0, 11, kUpb_FieldMode_Scalar | (UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(8, 1), UPB_SIZE(5, 5), kUpb_NoSub, 8, kUpb_FieldMode_Scalar | (kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(9, 2), UPB_SIZE(6, 6), kUpb_NoSub, 8, kUpb_FieldMode_Scalar | (kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google_protobuf_MethodDescriptorProto_msg_init = {
  &google_protobuf_MethodDescriptorProto_submsgs[0],
  &google_protobuf_MethodDescriptorProto__fields[0],
  UPB_SIZE(40, 64), 6, kUpb_ExtMode_NonExtendable, 6, 255, 0,
};

static const upb_MiniTable_Sub google_protobuf_FileOptions_submsgs[2] = {
  {.subenum = &google_protobuf_FileOptions_OptimizeMode_enum_init},
  {.submsg = &google_protobuf_UninterpretedOption_msg_init},
};

static const upb_MiniTable_Field google_protobuf_FileOptions__fields[21] = {
  {1, UPB_SIZE(24, 24), UPB_SIZE(1, 1), kUpb_NoSub, 12, kUpb_FieldMode_Scalar | kUpb_LabelFlags_IsAlternate | (kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {8, UPB_SIZE(32, 40), UPB_SIZE(2, 2), kUpb_NoSub, 12, kUpb_FieldMode_Scalar | kUpb_LabelFlags_IsAlternate | (kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {9, UPB_SIZE(4, 4), UPB_SIZE(3, 3), 0, 14, kUpb_FieldMode_Scalar | (kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {10, UPB_SIZE(8, 8), UPB_SIZE(4, 4), kUpb_NoSub, 8, kUpb_FieldMode_Scalar | (kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {11, UPB_SIZE(40, 56), UPB_SIZE(5, 5), kUpb_NoSub, 12, kUpb_FieldMode_Scalar | kUpb_LabelFlags_IsAlternate | (kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {16, UPB_SIZE(9, 9), UPB_SIZE(6, 6), kUpb_NoSub, 8, kUpb_FieldMode_Scalar | (kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {17, UPB_SIZE(10, 10), UPB_SIZE(7, 7), kUpb_NoSub, 8, kUpb_FieldMode_Scalar | (kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {18, UPB_SIZE(11, 11), UPB_SIZE(8, 8), kUpb_NoSub, 8, kUpb_FieldMode_Scalar | (kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {20, UPB_SIZE(12, 12), UPB_SIZE(9, 9), kUpb_NoSub, 8, kUpb_FieldMode_Scalar | (kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {23, UPB_SIZE(13, 13), UPB_SIZE(10, 10), kUpb_NoSub, 8, kUpb_FieldMode_Scalar | (kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {27, UPB_SIZE(14, 14), UPB_SIZE(11, 11), kUpb_NoSub, 8, kUpb_FieldMode_Scalar | (kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {31, UPB_SIZE(15, 15), UPB_SIZE(12, 12), kUpb_NoSub, 8, kUpb_FieldMode_Scalar | (kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {36, UPB_SIZE(48, 72), UPB_SIZE(13, 13), kUpb_NoSub, 12, kUpb_FieldMode_Scalar | kUpb_LabelFlags_IsAlternate | (kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {37, UPB_SIZE(56, 88), UPB_SIZE(14, 14), kUpb_NoSub, 12, kUpb_FieldMode_Scalar | kUpb_LabelFlags_IsAlternate | (kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {39, UPB_SIZE(64, 104), UPB_SIZE(15, 15), kUpb_NoSub, 12, kUpb_FieldMode_Scalar | kUpb_LabelFlags_IsAlternate | (kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {40, UPB_SIZE(72, 120), UPB_SIZE(16, 16), kUpb_NoSub, 12, kUpb_FieldMode_Scalar | kUpb_LabelFlags_IsAlternate | (kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {41, UPB_SIZE(80, 136), UPB_SIZE(17, 17), kUpb_NoSub, 12, kUpb_FieldMode_Scalar | kUpb_LabelFlags_IsAlternate | (kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {42, UPB_SIZE(16, 16), UPB_SIZE(18, 18), kUpb_NoSub, 8, kUpb_FieldMode_Scalar | (kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {44, UPB_SIZE(88, 152), UPB_SIZE(19, 19), kUpb_NoSub, 12, kUpb_FieldMode_Scalar | kUpb_LabelFlags_IsAlternate | (kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {45, UPB_SIZE(96, 168), UPB_SIZE(20, 20), kUpb_NoSub, 12, kUpb_FieldMode_Scalar | kUpb_LabelFlags_IsAlternate | (kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {999, UPB_SIZE(20, 184), UPB_SIZE(0, 0), 1, 11, kUpb_FieldMode_Array | (UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google_protobuf_FileOptions_msg_init = {
  &google_protobuf_FileOptions_submsgs[0],
  &google_protobuf_FileOptions__fields[0],
  UPB_SIZE(104, 192), 21, kUpb_ExtMode_Extendable, 1, 255, 0,
};

static const upb_MiniTable_Sub google_protobuf_MessageOptions_submsgs[1] = {
  {.submsg = &google_protobuf_UninterpretedOption_msg_init},
};

static const upb_MiniTable_Field google_protobuf_MessageOptions__fields[5] = {
  {1, UPB_SIZE(1, 1), UPB_SIZE(1, 1), kUpb_NoSub, 8, kUpb_FieldMode_Scalar | (kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(2, 2), UPB_SIZE(2, 2), kUpb_NoSub, 8, kUpb_FieldMode_Scalar | (kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(3, 3), UPB_SIZE(3, 3), kUpb_NoSub, 8, kUpb_FieldMode_Scalar | (kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(4, 4), UPB_SIZE(4, 4), kUpb_NoSub, 8, kUpb_FieldMode_Scalar | (kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {999, UPB_SIZE(8, 8), UPB_SIZE(0, 0), 0, 11, kUpb_FieldMode_Array | (UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google_protobuf_MessageOptions_msg_init = {
  &google_protobuf_MessageOptions_submsgs[0],
  &google_protobuf_MessageOptions__fields[0],
  UPB_SIZE(16, 16), 5, kUpb_ExtMode_Extendable, 3, 255, 0,
};

static const upb_MiniTable_Sub google_protobuf_FieldOptions_submsgs[3] = {
  {.subenum = &google_protobuf_FieldOptions_CType_enum_init},
  {.subenum = &google_protobuf_FieldOptions_JSType_enum_init},
  {.submsg = &google_protobuf_UninterpretedOption_msg_init},
};

static const upb_MiniTable_Field google_protobuf_FieldOptions__fields[8] = {
  {1, UPB_SIZE(4, 4), UPB_SIZE(1, 1), 0, 14, kUpb_FieldMode_Scalar | (kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(8, 8), UPB_SIZE(2, 2), kUpb_NoSub, 8, kUpb_FieldMode_Scalar | (kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(9, 9), UPB_SIZE(3, 3), kUpb_NoSub, 8, kUpb_FieldMode_Scalar | (kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(10, 10), UPB_SIZE(4, 4), kUpb_NoSub, 8, kUpb_FieldMode_Scalar | (kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(12, 12), UPB_SIZE(5, 5), 1, 14, kUpb_FieldMode_Scalar | (kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {10, UPB_SIZE(16, 16), UPB_SIZE(6, 6), kUpb_NoSub, 8, kUpb_FieldMode_Scalar | (kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {15, UPB_SIZE(17, 17), UPB_SIZE(7, 7), kUpb_NoSub, 8, kUpb_FieldMode_Scalar | (kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {999, UPB_SIZE(20, 24), UPB_SIZE(0, 0), 2, 11, kUpb_FieldMode_Array | (UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google_protobuf_FieldOptions_msg_init = {
  &google_protobuf_FieldOptions_submsgs[0],
  &google_protobuf_FieldOptions__fields[0],
  UPB_SIZE(24, 32), 8, kUpb_ExtMode_Extendable, 3, 255, 0,
};

static const upb_MiniTable_Sub google_protobuf_OneofOptions_submsgs[1] = {
  {.submsg = &google_protobuf_UninterpretedOption_msg_init},
};

static const upb_MiniTable_Field google_protobuf_OneofOptions__fields[1] = {
  {999, UPB_SIZE(0, 0), UPB_SIZE(0, 0), 0, 11, kUpb_FieldMode_Array | (UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google_protobuf_OneofOptions_msg_init = {
  &google_protobuf_OneofOptions_submsgs[0],
  &google_protobuf_OneofOptions__fields[0],
  UPB_SIZE(8, 8), 1, kUpb_ExtMode_Extendable, 0, 255, 0,
};

static const upb_MiniTable_Sub google_protobuf_EnumOptions_submsgs[1] = {
  {.submsg = &google_protobuf_UninterpretedOption_msg_init},
};

static const upb_MiniTable_Field google_protobuf_EnumOptions__fields[3] = {
  {2, UPB_SIZE(1, 1), UPB_SIZE(1, 1), kUpb_NoSub, 8, kUpb_FieldMode_Scalar | (kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(2, 2), UPB_SIZE(2, 2), kUpb_NoSub, 8, kUpb_FieldMode_Scalar | (kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {999, UPB_SIZE(4, 8), UPB_SIZE(0, 0), 0, 11, kUpb_FieldMode_Array | (UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google_protobuf_EnumOptions_msg_init = {
  &google_protobuf_EnumOptions_submsgs[0],
  &google_protobuf_EnumOptions__fields[0],
  UPB_SIZE(8, 16), 3, kUpb_ExtMode_Extendable, 0, 255, 0,
};

static const upb_MiniTable_Sub google_protobuf_EnumValueOptions_submsgs[1] = {
  {.submsg = &google_protobuf_UninterpretedOption_msg_init},
};

static const upb_MiniTable_Field google_protobuf_EnumValueOptions__fields[2] = {
  {1, UPB_SIZE(1, 1), UPB_SIZE(1, 1), kUpb_NoSub, 8, kUpb_FieldMode_Scalar | (kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {999, UPB_SIZE(4, 8), UPB_SIZE(0, 0), 0, 11, kUpb_FieldMode_Array | (UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google_protobuf_EnumValueOptions_msg_init = {
  &google_protobuf_EnumValueOptions_submsgs[0],
  &google_protobuf_EnumValueOptions__fields[0],
  UPB_SIZE(8, 16), 2, kUpb_ExtMode_Extendable, 1, 255, 0,
};

static const upb_MiniTable_Sub google_protobuf_ServiceOptions_submsgs[1] = {
  {.submsg = &google_protobuf_UninterpretedOption_msg_init},
};

static const upb_MiniTable_Field google_protobuf_ServiceOptions__fields[2] = {
  {33, UPB_SIZE(1, 1), UPB_SIZE(1, 1), kUpb_NoSub, 8, kUpb_FieldMode_Scalar | (kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {999, UPB_SIZE(4, 8), UPB_SIZE(0, 0), 0, 11, kUpb_FieldMode_Array | (UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google_protobuf_ServiceOptions_msg_init = {
  &google_protobuf_ServiceOptions_submsgs[0],
  &google_protobuf_ServiceOptions__fields[0],
  UPB_SIZE(8, 16), 2, kUpb_ExtMode_Extendable, 0, 255, 0,
};

static const upb_MiniTable_Sub google_protobuf_MethodOptions_submsgs[2] = {
  {.subenum = &google_protobuf_MethodOptions_IdempotencyLevel_enum_init},
  {.submsg = &google_protobuf_UninterpretedOption_msg_init},
};

static const upb_MiniTable_Field google_protobuf_MethodOptions__fields[3] = {
  {33, UPB_SIZE(1, 1), UPB_SIZE(1, 1), kUpb_NoSub, 8, kUpb_FieldMode_Scalar | (kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {34, UPB_SIZE(4, 4), UPB_SIZE(2, 2), 0, 14, kUpb_FieldMode_Scalar | (kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {999, UPB_SIZE(8, 8), UPB_SIZE(0, 0), 1, 11, kUpb_FieldMode_Array | (UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google_protobuf_MethodOptions_msg_init = {
  &google_protobuf_MethodOptions_submsgs[0],
  &google_protobuf_MethodOptions__fields[0],
  UPB_SIZE(16, 16), 3, kUpb_ExtMode_Extendable, 0, 255, 0,
};

static const upb_MiniTable_Sub google_protobuf_UninterpretedOption_submsgs[1] = {
  {.submsg = &google_protobuf_UninterpretedOption_NamePart_msg_init},
};

static const upb_MiniTable_Field google_protobuf_UninterpretedOption__fields[7] = {
  {2, UPB_SIZE(4, 8), UPB_SIZE(0, 0), 0, 11, kUpb_FieldMode_Array | (UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(8, 16), UPB_SIZE(1, 1), kUpb_NoSub, 12, kUpb_FieldMode_Scalar | kUpb_LabelFlags_IsAlternate | (kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(16, 32), UPB_SIZE(2, 2), kUpb_NoSub, 4, kUpb_FieldMode_Scalar | (kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(24, 40), UPB_SIZE(3, 3), kUpb_NoSub, 3, kUpb_FieldMode_Scalar | (kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(32, 48), UPB_SIZE(4, 4), kUpb_NoSub, 1, kUpb_FieldMode_Scalar | (kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(40, 56), UPB_SIZE(5, 5), kUpb_NoSub, 12, kUpb_FieldMode_Scalar | (kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {8, UPB_SIZE(48, 72), UPB_SIZE(6, 6), kUpb_NoSub, 12, kUpb_FieldMode_Scalar | kUpb_LabelFlags_IsAlternate | (kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google_protobuf_UninterpretedOption_msg_init = {
  &google_protobuf_UninterpretedOption_submsgs[0],
  &google_protobuf_UninterpretedOption__fields[0],
  UPB_SIZE(56, 88), 7, kUpb_ExtMode_NonExtendable, 0, 255, 0,
};

static const upb_MiniTable_Field google_protobuf_UninterpretedOption_NamePart__fields[2] = {
  {1, UPB_SIZE(4, 8), UPB_SIZE(1, 1), kUpb_NoSub, 12, kUpb_FieldMode_Scalar | kUpb_LabelFlags_IsAlternate | (kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(1, 1), UPB_SIZE(2, 2), kUpb_NoSub, 8, kUpb_FieldMode_Scalar | (kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google_protobuf_UninterpretedOption_NamePart_msg_init = {
  NULL,
  &google_protobuf_UninterpretedOption_NamePart__fields[0],
  UPB_SIZE(16, 24), 2, kUpb_ExtMode_NonExtendable, 2, 255, 2,
};

static const upb_MiniTable_Sub google_protobuf_SourceCodeInfo_submsgs[1] = {
  {.submsg = &google_protobuf_SourceCodeInfo_Location_msg_init},
};

static const upb_MiniTable_Field google_protobuf_SourceCodeInfo__fields[1] = {
  {1, UPB_SIZE(0, 0), UPB_SIZE(0, 0), 0, 11, kUpb_FieldMode_Array | (UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google_protobuf_SourceCodeInfo_msg_init = {
  &google_protobuf_SourceCodeInfo_submsgs[0],
  &google_protobuf_SourceCodeInfo__fields[0],
  UPB_SIZE(8, 8), 1, kUpb_ExtMode_NonExtendable, 1, 255, 0,
};

static const upb_MiniTable_Field google_protobuf_SourceCodeInfo_Location__fields[5] = {
  {1, UPB_SIZE(4, 8), UPB_SIZE(0, 0), kUpb_NoSub, 5, kUpb_FieldMode_Array | kUpb_LabelFlags_IsPacked | (UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(8, 16), UPB_SIZE(0, 0), kUpb_NoSub, 5, kUpb_FieldMode_Array | kUpb_LabelFlags_IsPacked | (UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(16, 24), UPB_SIZE(1, 1), kUpb_NoSub, 12, kUpb_FieldMode_Scalar | kUpb_LabelFlags_IsAlternate | (kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(24, 40), UPB_SIZE(2, 2), kUpb_NoSub, 12, kUpb_FieldMode_Scalar | kUpb_LabelFlags_IsAlternate | (kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(12, 56), UPB_SIZE(0, 0), kUpb_NoSub, 12, kUpb_FieldMode_Array | kUpb_LabelFlags_IsAlternate | (UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google_protobuf_SourceCodeInfo_Location_msg_init = {
  NULL,
  &google_protobuf_SourceCodeInfo_Location__fields[0],
  UPB_SIZE(32, 64), 5, kUpb_ExtMode_NonExtendable, 4, 255, 0,
};

static const upb_MiniTable_Sub google_protobuf_GeneratedCodeInfo_submsgs[1] = {
  {.submsg = &google_protobuf_GeneratedCodeInfo_Annotation_msg_init},
};

static const upb_MiniTable_Field google_protobuf_GeneratedCodeInfo__fields[1] = {
  {1, UPB_SIZE(0, 0), UPB_SIZE(0, 0), 0, 11, kUpb_FieldMode_Array | (UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google_protobuf_GeneratedCodeInfo_msg_init = {
  &google_protobuf_GeneratedCodeInfo_submsgs[0],
  &google_protobuf_GeneratedCodeInfo__fields[0],
  UPB_SIZE(8, 8), 1, kUpb_ExtMode_NonExtendable, 1, 255, 0,
};

static const upb_MiniTable_Sub google_protobuf_GeneratedCodeInfo_Annotation_submsgs[1] = {
  {.subenum = &google_protobuf_GeneratedCodeInfo_Annotation_Semantic_enum_init},
};

static const upb_MiniTable_Field google_protobuf_GeneratedCodeInfo_Annotation__fields[5] = {
  {1, UPB_SIZE(4, 16), UPB_SIZE(0, 0), kUpb_NoSub, 5, kUpb_FieldMode_Array | kUpb_LabelFlags_IsPacked | (UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(20, 24), UPB_SIZE(1, 1), kUpb_NoSub, 12, kUpb_FieldMode_Scalar | kUpb_LabelFlags_IsAlternate | (kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(8, 4), UPB_SIZE(2, 2), kUpb_NoSub, 5, kUpb_FieldMode_Scalar | (kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(12, 8), UPB_SIZE(3, 3), kUpb_NoSub, 5, kUpb_FieldMode_Scalar | (kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(16, 12), UPB_SIZE(4, 4), 0, 14, kUpb_FieldMode_Scalar | (kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google_protobuf_GeneratedCodeInfo_Annotation_msg_init = {
  &google_protobuf_GeneratedCodeInfo_Annotation_submsgs[0],
  &google_protobuf_GeneratedCodeInfo_Annotation__fields[0],
  UPB_SIZE(32, 40), 5, kUpb_ExtMode_NonExtendable, 5, 255, 0,
};

static const upb_MiniTable *messages_layout[27] = {
  &google_protobuf_FileDescriptorSet_msg_init,
  &google_protobuf_FileDescriptorProto_msg_init,
  &google_protobuf_DescriptorProto_msg_init,
  &google_protobuf_DescriptorProto_ExtensionRange_msg_init,
  &google_protobuf_DescriptorProto_ReservedRange_msg_init,
  &google_protobuf_ExtensionRangeOptions_msg_init,
  &google_protobuf_FieldDescriptorProto_msg_init,
  &google_protobuf_OneofDescriptorProto_msg_init,
  &google_protobuf_EnumDescriptorProto_msg_init,
  &google_protobuf_EnumDescriptorProto_EnumReservedRange_msg_init,
  &google_protobuf_EnumValueDescriptorProto_msg_init,
  &google_protobuf_ServiceDescriptorProto_msg_init,
  &google_protobuf_MethodDescriptorProto_msg_init,
  &google_protobuf_FileOptions_msg_init,
  &google_protobuf_MessageOptions_msg_init,
  &google_protobuf_FieldOptions_msg_init,
  &google_protobuf_OneofOptions_msg_init,
  &google_protobuf_EnumOptions_msg_init,
  &google_protobuf_EnumValueOptions_msg_init,
  &google_protobuf_ServiceOptions_msg_init,
  &google_protobuf_MethodOptions_msg_init,
  &google_protobuf_UninterpretedOption_msg_init,
  &google_protobuf_UninterpretedOption_NamePart_msg_init,
  &google_protobuf_SourceCodeInfo_msg_init,
  &google_protobuf_SourceCodeInfo_Location_msg_init,
  &google_protobuf_GeneratedCodeInfo_msg_init,
  &google_protobuf_GeneratedCodeInfo_Annotation_msg_init,
};

const upb_MiniTable_Enum google_protobuf_FieldDescriptorProto_Type_enum_init = {
    64,
    0,
    {
        0x7fffe,
        0x0,
    },
};

const upb_MiniTable_Enum google_protobuf_FieldDescriptorProto_Label_enum_init = {
    64,
    0,
    {
        0xe,
        0x0,
    },
};

const upb_MiniTable_Enum google_protobuf_FileOptions_OptimizeMode_enum_init = {
    64,
    0,
    {
        0xe,
        0x0,
    },
};

const upb_MiniTable_Enum google_protobuf_FieldOptions_CType_enum_init = {
    64,
    0,
    {
        0x7,
        0x0,
    },
};

const upb_MiniTable_Enum google_protobuf_FieldOptions_JSType_enum_init = {
    64,
    0,
    {
        0x7,
        0x0,
    },
};

const upb_MiniTable_Enum google_protobuf_MethodOptions_IdempotencyLevel_enum_init = {
    64,
    0,
    {
        0x7,
        0x0,
    },
};

const upb_MiniTable_Enum google_protobuf_GeneratedCodeInfo_Annotation_Semantic_enum_init = {
    64,
    0,
    {
        0x7,
        0x0,
    },
};

static const upb_MiniTable_Enum *enums_layout[7] = {
  &google_protobuf_FieldDescriptorProto_Type_enum_init,
  &google_protobuf_FieldDescriptorProto_Label_enum_init,
  &google_protobuf_FileOptions_OptimizeMode_enum_init,
  &google_protobuf_FieldOptions_CType_enum_init,
  &google_protobuf_FieldOptions_JSType_enum_init,
  &google_protobuf_MethodOptions_IdempotencyLevel_enum_init,
  &google_protobuf_GeneratedCodeInfo_Annotation_Semantic_enum_init,
};

const upb_MiniTable_File google_protobuf_descriptor_proto_upb_file_layout = {
  messages_layout,
  enums_layout,
  NULL,
  27,
  7,
  0,
};

#include "upb/port_undef.inc"
