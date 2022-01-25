// Copyright 2022 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <xnnpack/common.h>
#include <xnnpack/aarch64-assembler.h>

#include <cmath>

namespace xnnpack {
namespace aarch64 {
// Min and max values for the imm7 for ldp, will be shifted right by 3 when encoding.
constexpr int32_t kImm7Min = -512;
constexpr int32_t kImm7Max = 504;
constexpr uint32_t kImm7Mask = 0x7F;
// Max value for imm12, will be shifted right by 3 when encoding.
constexpr int32_t kImm12Max = 32760;
constexpr uint32_t kUint12Max = 4095;

constexpr int32_t kInt9Max = 255;
constexpr int32_t kInt9Min = -256;
constexpr uint32_t kImm9Mask = 0x1FF;

// Constants used for checking branch offset bounds.
// Conditional bounds are +/-1MB.
constexpr ptrdiff_t kConditionalBranchImmMax = 1048572;
constexpr ptrdiff_t kConditionalBranchImmMin = -1048576;
// TBZ and TBNZ bounds are +/-32KB.
constexpr ptrdiff_t kTbxzImmMax = 32764;
constexpr ptrdiff_t kTbxzImmMin = -32768;
// Unconditional bounds are +/-128MB.
constexpr ptrdiff_t kUnconditionalBranchImmMax = 134217727;
constexpr ptrdiff_t kUnconditionalBranchImmMin = -134217728;

constexpr uint32_t kConditionalImmMask = 0x0007FFFF;
constexpr uint32_t kTbxzImmMask = 0x3FFF;
constexpr uint32_t kUnconditionalImmMask = 0x03FFFFFF;

template <typename Reg> inline uint32_t rd(Reg vn) { return vn.code; }
template <typename Reg> inline uint32_t rt(Reg qn) { return qn.code; }
inline uint32_t rt2(QRegister qn) { return qn.code << 10; }
template <typename Reg> inline uint32_t rm(Reg xn) { return xn.code << 16; }
template <typename Reg> inline uint32_t rn(Reg rn) { return rn.code << 5; }
inline uint32_t q(VRegister vt) { return vt.q << 30; }
inline uint32_t size(VRegister vt) { return vt.size << 10; }
inline uint32_t fp_sz(VRegister vn) { return vn.is_s() ? 0 : 1 << 22; }

inline bool is_same_shape(VRegister vt1, VRegister vt2) {
  return vt1.size == vt2.size && vt1.q == vt2.q;
}

template <typename Reg, typename... Regs>
inline bool is_same_shape(Reg reg1, Reg reg2, Regs... regs) {
  return is_same_shape(reg1, reg2) && is_same_shape(reg2, regs...);
}

inline bool is_same_shape(VRegisterList vs) {
  switch (vs.length) {
    case 1:
      return true;
    case 2:
      return is_same_shape(vs.vt1, vs.vt2);
    case 3:
      return is_same_shape(vs.vt1, vs.vt2, vs.vt3);
    case 4:
      return is_same_shape(vs.vt1, vs.vt2, vs.vt3, vs.vt4);
    default:
      XNN_UNREACHABLE;
  }
}

inline bool is_same_data_type(VRegister vt1, VRegisterLane vt2) {
  return vt1.size == vt2.size;
}

inline bool is_consecutive(VRegister vt1, VRegister vt2) {
  return (vt1.code + 1) % 32 == vt2.code;
}

template <typename Reg, typename... Regs>
inline bool is_consecutive(Reg reg1, Reg reg2, Regs... regs) {
  return is_consecutive(reg1, reg2) && is_consecutive(reg2, regs...);
}

inline bool is_consecutive(VRegisterList vs) {
  switch (vs.length) {
    case 1:
      return true;
    case 2:
      return is_consecutive(vs.vt1, vs.vt2);
    case 3:
      return is_consecutive(vs.vt1, vs.vt2, vs.vt3);
    case 4:
      return is_consecutive(vs.vt1, vs.vt2, vs.vt3, vs.vt4);
    default:
      XNN_UNREACHABLE;
  }
}

// Check if a branch offset is valid, it must fit in 19 bits.
inline bool branch_offset_valid(ptrdiff_t offset, BranchType branch_type) {
  switch (branch_type) {
    case BranchType::kConditional:
      return offset < kConditionalBranchImmMax && offset > kConditionalBranchImmMin;
    case BranchType::kTbxz:
      return offset < kTbxzImmMax && offset > kTbxzImmMin;
    case BranchType::kUnconditional:
      return offset < kUnconditionalBranchImmMax && offset > kUnconditionalBranchImmMin;
  }
}

inline BranchType instruction_branch_type(uint32_t* instr) {
  const uint32_t masked = *instr & 0xFE000000;
  switch (masked) {
    case 0xB6000000:
    case 0x36000000:
      return BranchType::kTbxz;
    case 0x54000000:
      return BranchType::kConditional;
    case 0x14000000:
    case 0x16000000:
      return BranchType::kUnconditional;
    default:
      XNN_UNREACHABLE;
  }
}

inline uint32_t mask(BranchType branch_type) {
  switch (branch_type) {
    case BranchType::kConditional:
      return kConditionalImmMask;
    case BranchType::kTbxz:
      return kTbxzImmMask;
    case BranchType::kUnconditional:
      return kUnconditionalImmMask;
  }
}

inline uint8_t shift(BranchType branch_type) {
  switch (branch_type) {
    case BranchType::kConditional:
      return 5;
    case BranchType::kTbxz:
      return 5;
    case BranchType::kUnconditional:
      return 0;
  }
}

inline uint32_t branch_imm(ptrdiff_t offset, BranchType bt) {
  return ((offset >> kInstructionSizeInBytesLog2) & mask(bt)) << shift(bt);
}

inline uint32_t hl(VRegisterLane vl) {
  if (vl.is_s()) {
    return (vl.lane & 1) << 21 | ((vl.lane & 2) << 10);
  } else {
    return (vl.lane & 1) << 11;
  }
}

inline bool lane_index_valid(uint8_t q, uint8_t size, uint8_t lane) {
  // The logic here is something like:
  // if (q && size == 0) {
  //   return lane < 16;
  // } else if (q && size == 1) {
  //   return lane < 8;
  // } else if (q && size == 2) {
  //   return lane < 4;
  // } else if (q && size == 3) {
  //   return lane < 2;
  // }
  // then repeat for !q with maximum lane size halved.
  // translated into this formula.
  return lane < ((q + 1) << (3 - size));
}

inline uint8_t load_store_opcode(uint8_t register_length) {
  switch (register_length) {
    case 1:
      return 0x7;
    case 2:
      return 0xA;
    case 3:
      return 0x6;
    case 4:
      return 0x2;
    default:
      XNN_UNREACHABLE;
  }
}

inline bool imm7_offset_valid(int32_t imm, XRegister xn) {
  return imm >= kImm7Min && imm <= kImm7Max && (imm & 0x7) == 0;
}

inline bool imm7_offset_valid(int32_t imm, QRegister qn) {
  return imm >= (kImm7Min * 2) && imm <= (kImm7Max * 2) && (imm & 0xF) == 0;
}

// Base instructions.

Assembler& Assembler::add(XRegister xd, XRegister xn, uint16_t imm12) {
  // The instruction supports larger numbers using the shift by (left shift by 12), but that's unused in kernels.
  if (imm12 > kUint12Max) {
    error_ = Error::kInvalidOperand;
    return *this;
  }

  return emit32(0x91000000 | imm12 << 10 | rn(xn) | rd(xd));
}

Assembler& Assembler::b(Label& l) {
  return branch_to_label(0x14000000, BranchType::kUnconditional, l);
}

Assembler& Assembler::ldp(XRegister xt1, XRegister xt2, MemOperand xn) {
  if (!imm7_offset_valid(xn.offset, xt1)) {
    error_ = Error::kInvalidOperand;
    return *this;
  }

  const uint32_t mode = xn.mode == AddressingMode::kOffset ? 2 : 1;
  const uint32_t offset = (xn.offset >> 3) & kImm7Mask;

  return emit32(0xA8400000 | mode << 23 | offset << 15 | xt2.code << 10 | rn(xn.base) | xt1.code);
}

Assembler& Assembler::ldp(XRegister xt1, XRegister xt2, MemOperand xn, int32_t imm) {
  if (xn.offset != 0) {
    error_ = Error::kInvalidOperand;
    return *this;
  }
  return ldp(xt1, xt2, {xn.base, imm, AddressingMode::kPostIndex});
}

Assembler& Assembler::ldr(XRegister xt, MemOperand xn) {
  const int32_t imm = xn.offset;
  if (xn.mode != AddressingMode::kOffset || imm < 0 || imm > (kUint12Max << 3) || (imm & 7) != 0) {
    error_ = Error::kInvalidOperand;
    return *this;
  }

  return emit32(0xF9400000 | imm >> 3 << 10 | rn(xn.base) | xt.code);
}

Assembler& Assembler::prfm(PrefetchOp prfop, MemOperand xn) {
  if (xn.offset < 0 || xn.offset > kImm12Max) {
    error_ = Error::kInvalidOperand;
    return *this;
  }

  return emit32(0xF9800000 | xn.offset << 10 | rn(xn.base) | static_cast<uint32_t>(prfop));
}

Assembler& Assembler::ret() {
  return emit32(0xD65F0000 | rn(x30));
}

Assembler& Assembler::sub(XRegister xd, XRegister xn, XRegister xm) {
  return emit32(0xCB000000 | rm(xm) | rn(xn) | rd(xd));
}

Assembler& Assembler::subs(XRegister xd, XRegister xn, uint16_t imm12) {
  if (imm12 > kUint12Max) {
    error_ = Error::kInvalidOperand;
    return *this;
  }

  return emit32(0xF1000000 | imm12 << 10 | rn(xn) | rd(xd));
}

Assembler& Assembler::tbnz(XRegister xd, uint8_t bit, Label& l) {
  return tb_helper(0x37000000, xd, bit, l);
}

Assembler& Assembler::tbz(XRegister xd, uint8_t bit, Label& l) {
  return tb_helper(0x36000000, xd, bit, l);
}

// SIMD instructions.

Assembler& Assembler::dup(DRegister dd, VRegisterLane vn) {
  if (vn.size != 3 || vn.lane > 1) {
    error_ = Error::kInvalidOperand;
    return *this;
  }
  const uint8_t imm5 = 0b1000 | (vn.lane & 1) << 4;
  return emit32(0x5E000400 | imm5 << 16 | rn(vn) | rd(dd));
}

Assembler& Assembler::fadd(VRegister vd, VRegister vn, VRegister vm) {
  if (!is_same_shape(vd, vn, vm)) {
    error_ = Error::kInvalidOperand;
    return *this;
  }

  return emit32(0x0E20D400 | q(vd) | fp_sz(vn) | rm(vm) | rn(vn) | rd(vd));
}

Assembler& Assembler::fmax(VRegister vd, VRegister vn, VRegister vm) {
  if (!is_same_shape(vd, vn, vm)) {
    error_ = Error::kInvalidOperand;
    return *this;
  }

  return emit32(0x0E20F400 | q(vd) | fp_sz(vn) | rm(vm) | rn(vn) | rd(vd));
}

Assembler& Assembler::fmin(VRegister vd, VRegister vn, VRegister vm) {
  if (!is_same_shape(vd, vn, vm)) {
    error_ = Error::kInvalidOperand;
    return *this;
  }

  return emit32(0x0EA0F400 | q(vd) | fp_sz(vn) | rm(vm) | rn(vn) | rd(vd));
}

Assembler& Assembler::fmla(VRegister vd, VRegister vn, VRegisterLane vm) {
  if (!is_same_shape(vd, vn) || !is_same_data_type(vd, vm)) {
    error_ = Error::kInvalidOperand;
    return *this;
  }
  if (!lane_index_valid(vd.q, vm.size, vm.lane)) {
    error_ = Error::kInvalidLaneIndex;
    return *this;
  }

  return emit32(0x0F801000 | q(vd) | fp_sz(vd) | hl(vm) | rm(vm) | rn(vn) | rd(vd));
}

Assembler& Assembler::ld1(VRegisterList vs, MemOperand xn, int32_t imm) {
  VRegister vt = vs.vt1;

  if (!is_same_shape(vs) || !is_consecutive(vs)) {
    error_ = Error::kInvalidOperand;
    return *this;
  }

  // imm must match number of bytes loaded.
  if ((vt.q + 1) * 8 * vs.length != imm) {
    error_ = Error::kInvalidOperand;
    return *this;
  }

  const uint8_t opcode = load_store_opcode(vs.length);

  return emit32(0x0CDF0000 | q(vt) | opcode << 12 | size(vt) | rn(xn.base) | rt(vt));
}

Assembler& Assembler::ld2r(VRegisterList xs, MemOperand xn) {
  if (xs.length != 2 || !is_same_shape(xs.vt1, xs.vt2) || xn.offset != 0) {
    error_ = Error::kInvalidOperand;
    return *this;
  }

  return emit32(0x0D60C000 | q(xs.vt1) | size(xs.vt1) | rn(xn.base) | xs.vt1.code);
}

Assembler& Assembler::ldp(QRegister qt1, QRegister qt2, MemOperand xn, int32_t imm) {
  if (!imm7_offset_valid(imm, qt1)) {
    error_ = Error::kInvalidOperand;
    return *this;
  }
  const uint32_t offset = (imm >> 4) & kImm7Mask;

  return emit32(0xACC00000 | offset << 15 | rt2(qt2) | rn(xn.base) | qt1.code);
}

Assembler& Assembler::ldr(DRegister dt, MemOperand xn, int32_t imm) {
  return ldr(/*size=*/3, /*opc=*/1, xn, imm, dt.code);
}

Assembler& Assembler::ldr(QRegister qt, MemOperand xn, int32_t imm) {
  return ldr(/*size=*/0, /*opc=*/3, xn, imm, qt.code);
}

Assembler& Assembler::ldr(SRegister st, MemOperand xn, int32_t imm) {
  return ldr(/*size=*/2, /*opc=*/1, xn, imm, st.code);
}

Assembler& Assembler::mov(VRegister vd, VRegister vn) {
  if (!is_same_shape(vd, vn)) {
    error_ = Error::kInvalidOperand;
    return *this;
  }
  return emit32(0x0EA01C00 | q(vd) | rm(vn) | rn(vn) | rd(vd));
}

Assembler& Assembler::movi(VRegister vd, uint8_t imm) {
  if (imm != 0) {
    error_ = Error::kUnimplemented;
    return *this;
  }

  uint32_t cmode = 0;
  switch (vd.size) {
    case 0:
      cmode = 0xE;
      break;
    case 1:
      cmode = 0x8;
      break;
    case 2:
      cmode = 0x0;
      break;
    default:
      error_ = Error::kUnimplemented;
      return *this;
  }

  return emit32(0x0F000400 | q(vd) | cmode << 12 | vd.code);
}

Assembler& Assembler::st1(VRegisterList vs, MemOperand xn, XRegister xm) {
  if (!is_same_shape(vs) || !is_consecutive(vs)) {
    error_ = Error::kInvalidOperand;
    return *this;
  }

  VRegister vt = vs.vt1;

  const uint8_t opcode = load_store_opcode(vs.length);
  return emit32(0x0C800000 | q(vt) | rm(xm) | opcode << 12 | size(vt) | rn(xn.base) | rt(vt));
}

Assembler& Assembler::stp(QRegister qt1, QRegister qt2, MemOperand xn, int32_t imm) {
  if (!imm7_offset_valid(imm, qt1)) {
    error_ = Error::kInvalidOperand;
    return *this;
  }

  const uint32_t offset = (imm >> 4) & kImm7Mask;
  return emit32(0xAC800000 | offset << 15 | rt2(qt2) | rn(xn.base) | rt(qt1));
}

Assembler& Assembler::str(DRegister dt, MemOperand xn, int32_t imm) {
  return str(/*size=*/3, /*opc=*/0, xn, imm, dt.code);
}

Assembler& Assembler::str(QRegister qt, MemOperand xn, int32_t imm) {
  return str(/*size=*/0, /*opc=*/2, xn, imm, qt.code);
}

Assembler& Assembler::str(SRegister st, MemOperand xn) {
  const int32_t imm = xn.offset;
  if (imm < 0 || imm > (kUint12Max << 2) || (imm & 0x3) != 0) {
    error_ = Error::kInvalidOperand;
    return *this;
  }

  return emit32(0xBD000000 | imm >> 2 << 10 | rn(xn.base) | rt(st));
}

Assembler& Assembler::emit32(uint32_t value) {
  if (error_ != Error::kNoError) {
    return *this;
  }

  if (cursor_ + sizeof(value) > top_) {
    error_ = Error::kOutOfMemory;
    return *this;
  }

  memcpy(cursor_, &value, sizeof(value));
  cursor_ += sizeof(value);
  return *this;
}

Assembler& Assembler::bind(Label& l) {
  if (l.bound) {
    error_ = Error::kLabelAlreadyBound;
    return *this;
  }

  l.bound = true;
  l.offset = cursor_;

  // Patch all users.
  for (size_t i = 0; i < l.num_users; i++) {
    byte* user = l.users[i];
    const ptrdiff_t offset = l.offset - user;

    const BranchType bt = instruction_branch_type(reinterpret_cast<uint32_t*>(user));
    if (!branch_offset_valid(offset, bt)) {
      error_ = Error::kLabelOffsetOutOfBounds;
      return *this;
    }

    *user = (*user | branch_imm(offset, bt));
  }
  return *this;
}

Assembler& Assembler::b(Condition c, Label& l) {
  return branch_to_label(0x54000000 | c, BranchType::kConditional, l);
}

Assembler& Assembler::branch_to_label(uint32_t opcode, BranchType bt, Label& l) {
  if (l.bound) {
    const ptrdiff_t offset = l.offset - cursor_;
    if (!branch_offset_valid(offset, bt)) {
      error_ = Error::kLabelOffsetOutOfBounds;
      return *this;
    }
    return emit32(opcode | branch_imm(offset, bt));
  } else {
    if (!l.add_use(cursor_)) {
      error_ = Error::kLabelHasTooManyUsers;
      return *this;
    }
    return emit32(opcode);
  }
}

Assembler& Assembler::ldr(uint32_t size, uint32_t opc, MemOperand xn, int32_t imm, uint8_t rt_code) {
  if (xn.mode != AddressingMode::kOffset || xn.offset != 0 || imm < kInt9Min || imm > kInt9Max) {
    error_ = Error::kInvalidOperand;
    return *this;
  }

  return emit32(0x3C400400 | size << 30 | opc << 22 | (imm & kImm9Mask) << 12| rn(xn.base) | rt_code);
}

Assembler& Assembler::str(uint32_t size, uint32_t opc, MemOperand xn, int32_t imm, uint8_t rt_code) {
  if (imm < kInt9Min || imm > kInt9Max) {
    error_ = Error::kInvalidOperand;
    return *this;
  }

  return emit32(0x3C000400 | size << 30 | opc << 22 | (imm & kImm9Mask) << 12 | rn(xn.base) | rt_code);
}

Assembler& Assembler::tb_helper(uint32_t op, XRegister xd, uint8_t bit, Label& l) {
  if (bit > 63) {
    error_ = Error::kInvalidOperand;
    return *this;
  }

  const uint32_t bit_pos = (bit & 0x20) >> 5 << 31 | (bit & 0x1F) << 19;
  return branch_to_label(op | bit_pos | xd.code, BranchType::kTbxz, l);
}

}  // namespace aarch64
}  // namespace xnnpack