#ifndef INCLUDE_ISA_HPP_
#define INCLUDE_ISA_HPP_

#include <cstdint>

namespace lowvm {
using addr = std::uint32_t;
using virt = addr;
using size = std::size_t;
using cell = std::uint32_t;
using ptr = void*;

namespace instructions {
enum Opcodes : cell {
  NOP = 0x0,
  HLT = 0x1,
  INT = 0x2,
  JMP = 0x3,
  JZ  = 0x4,
  MOV = 0x5,
  ADD = 0x6,
  MUL = 0x7,
  DIV = 0x8,
  OR  = 0x9,
  AND = 0xA,
  XOR = 0xB
};

enum Types : cell {
  ADDR = 0,
  VAL = 1
};

enum Sizes : cell {
  BYTE = 0,
  WORD = 1,
  DWORD = 2,
  QWORD = 3
};

constexpr cell i(
  Opcodes opcode = NOP,
  Types firstType = ADDR,
  Types secondType = ADDR
) {
  return opcode | (firstType << 31) | (secondType << 30);
}

enum Instructions : cell {
  /// Interrupt with header at farg addr
  INTV = i(INT, VAL),
  /// Interrupt with header at addr contains at farg addr
  INTA = i(INT, ADDR),

  /// Jump to farg addr
  JMPV = i(JMP, VAL),
  /// Jump to addr contains at farg addr
  JMPA = i(JMP, ADDR),
  /// Jump to farg addr if value at addr contains at sarg addr = 0
  JZVA = i(JZ, VAL),
  /// Jump to addr contains at farg addr
  /// if value at addr contains at sarg addr = 0
  JZAA = i(JZ, ADDR),
  /// Jump to farg addr if value contains at sarg addr = 0
  JZVV = i(JZ, VAL, VAL),
  /// Jump to addr contains at farg addr if value contains at sarg addr = 0
  JZAV = i(JZ, ADDR, VAL),

  /// Move farg value to addr contains at sarg addr
  MOVVA = i(MOV, VAL),
  /// Move value contains at farg addr to addr contains at sarg addr
  MOVAA = i(MOV, ADDR),
  /// Move farg value to sarg addr
  MOVVV = i(MOV, VAL, VAL),
  /// Move value contains in farg addr to sarg addr
  MOVAV = i(MOV, ADDR, VAL),

  /// Add farg value to value contains at sarg addr
  /// and move res to addr contains at sarg addr
  ADDVA = i(ADD, VAL),
  /// Add value contains at farg addr to value contains at sarg addr
  /// and move res to addr contains at sarg addr
  ADDAA = i(ADD, ADDR),
  /// Add farg value to value at sarg addr and move res to sarg addr
  ADDVV = i(ADD, VAL, VAL),
  /// Add value contains at farg addr to value at sarg addr
  /// and move res to sarg addr
  ADDAV = i(ADD, ADDR, VAL),
  /// Multiply farg value and value contains at sarg addr
  /// and move res to addr contains at sarg addr
  MULVA = i(MUL, VAL),
  /// Multiply value contains at farg addr and value contains at sarg addr
  /// and move res to addr contains at sarg addr
  MULAA = i(MUL, ADDR),
  /// Multiply farg value and value at sarg addr and move res to sarg addr
  MULVV = i(MUL, VAL, VAL),
  /// Multiply value contains at farg addr and value at sarg addr
  /// and move res to sarg addr
  MULAV = i(MUL, ADDR, VAL),
  DIVVA = i(DIV, VAL),
  DIVAA = i(DIV, ADDR),
  DIVVV = i(DIV, VAL, VAL),
  DIVAV = i(DIV, ADDR, VAL),

  ORVA = i(OR, VAL),
  ORAA = i(OR, ADDR),
  ORVV = i(OR, VAL, VAL),
  ORAV = i(OR, ADDR, VAL),
  ANDVA = i(AND, VAL),
  ANDAA = i(AND, ADDR),
  ANDVV = i(AND, VAL, VAL),
  ANDAV = i(AND, ADDR, VAL),
  XORVA = i(XOR, VAL),
  XORAA = i(XOR, ADDR),
  XORVV = i(XOR, VAL, VAL),
  XORAV = i(XOR, ADDR, VAL)
};
}  // namespace instructions
}  // namespace lowvm

#endif  // INCLUDE_ISA_HPP_
