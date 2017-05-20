#ifndef INCLUDE_ISA_HPP_
#define INCLUDE_ISA_HPP_

#include <cstdint>

namespace lowvm {
using addr = std::uint32_t;
using virt = addr;
using size = std::size_t;
using cell = std::uint32_t;
using ptr = void*;

enum class Interrupts : std::uint32_t {
  INVALID_SERVICE = 0,
  INVALID_INSTRUCTION = 1
};

template <typename T>
constexpr cell c(T from) {
  return static_cast<cell>(from);
}

namespace instructions {
enum class Opcodes : cell {
  NOP = 0x0,
  HLT = 0x1,
  SRV = 0x2,
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

enum class Types : cell {
  ADDR = 0,
  VAL = 1
};

enum class Sizes : cell {
  BYTE = 0,
  WORD = 1,
  DWORD = 2,
  QWORD = 3
};

constexpr cell i(
  Opcodes opcode = Opcodes::NOP,
  Types firstType = Types::ADDR,
  Types secondType = Types::ADDR
) {
  return c(opcode) |
    (c(firstType) << 31) |
    (c(secondType) << 30);
}

enum class Instructions : cell {
  /// Interrupt with header at farg addr
  SRVV = i(Opcodes::SRV, Types::VAL),
  /// Interrupt with header at addr contains at farg addr
  SRVA = i(Opcodes::SRV, Types::ADDR),

  /// Jump to farg addr
  JMPV = i(Opcodes::JMP, Types::VAL),
  /// Jump to addr contains at farg addr
  JMPA = i(Opcodes::JMP, Types::ADDR),
  /// Jump to farg addr if value at addr contains at sarg addr = 0
  JZVA = i(Opcodes::JZ, Types::VAL),
  /// Jump to addr contains at farg addr
  /// if value at addr contains at sarg addr = 0
  JZAA = i(Opcodes::JZ, Types::ADDR),
  /// Jump to farg addr if value contains at sarg addr = 0
  JZVV = i(Opcodes::JZ, Types::VAL, Types::VAL),
  /// Jump to addr contains at farg addr if value contains at sarg addr = 0
  JZAV = i(Opcodes::JZ, Types::ADDR, Types::VAL),

  /// Move farg value to addr contains at sarg addr
  MOVVA = i(Opcodes::MOV, Types::VAL),
  /// Move value contains at farg addr to addr contains at sarg addr
  MOVAA = i(Opcodes::MOV, Types::ADDR),
  /// Move farg value to sarg addr
  MOVVV = i(Opcodes::MOV, Types::VAL, Types::VAL),
  /// Move value contains in farg addr to sarg addr
  MOVAV = i(Opcodes::MOV, Types::ADDR, Types::VAL),

  /// Add farg value to value contains at sarg addr
  /// and move res to addr contains at sarg addr
  ADDVA = i(Opcodes::ADD, Types::VAL),
  /// Add value contains at farg addr to value contains at sarg addr
  /// and move res to addr contains at sarg addr
  ADDAA = i(Opcodes::ADD, Types::ADDR),
  /// Add farg value to value at sarg addr and move res to sarg addr
  ADDVV = i(Opcodes::ADD, Types::VAL, Types::VAL),
  /// Add value contains at farg addr to value at sarg addr
  /// and move res to sarg addr
  ADDAV = i(Opcodes::ADD, Types::ADDR, Types::VAL),
  /// Multiply farg value and value contains at sarg addr
  /// and move res to addr contains at sarg addr
  MULVA = i(Opcodes::MUL, Types::VAL),
  /// Multiply value contains at farg addr and value contains at sarg addr
  /// and move res to addr contains at sarg addr
  MULAA = i(Opcodes::MUL, Types::ADDR),
  /// Multiply farg value and value at sarg addr and move res to sarg addr
  MULVV = i(Opcodes::MUL, Types::VAL, Types::VAL),
  /// Multiply value contains at farg addr and value at sarg addr
  /// and move res to sarg addr
  MULAV = i(Opcodes::MUL, Types::ADDR, Types::VAL),
  DIVVA = i(Opcodes::DIV, Types::VAL),
  DIVAA = i(Opcodes::DIV, Types::ADDR),
  DIVVV = i(Opcodes::DIV, Types::VAL, Types::VAL),
  DIVAV = i(Opcodes::DIV, Types::ADDR, Types::VAL),

  ORVA = i(Opcodes::OR, Types::VAL),
  ORAA = i(Opcodes::OR, Types::ADDR),
  ORVV = i(Opcodes::OR, Types::VAL, Types::VAL),
  ORAV = i(Opcodes::OR, Types::ADDR, Types::VAL),
  ANDVA = i(Opcodes::AND, Types::VAL),
  ANDAA = i(Opcodes::AND, Types::ADDR),
  ANDVV = i(Opcodes::AND, Types::VAL, Types::VAL),
  ANDAV = i(Opcodes::AND, Types::ADDR, Types::VAL),
  XORVA = i(Opcodes::XOR, Types::VAL),
  XORAA = i(Opcodes::XOR, Types::ADDR),
  XORVV = i(Opcodes::XOR, Types::VAL, Types::VAL),
  XORAV = i(Opcodes::XOR, Types::ADDR, Types::VAL),
};
}  // namespace instructions
}  // namespace lowvm

#endif  // INCLUDE_ISA_HPP_
