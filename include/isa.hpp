#ifndef ISA_H
#define ISA_H

#include <cstdint>

namespace lowvm {
class VM;
class MU;
class Service;

using addr = std::size_t;
using size = std::size_t;
using ptr = void*;

namespace instructions {
namespace opcodes {
const std::uint8_t NOP = 0x0;
const std::uint8_t HLT = 0x1;
const std::uint8_t INT = 0x2;
const std::uint8_t JMP = 0x3;
const std::uint8_t JZ = 0x4;
const std::uint8_t MOV = 0x5;
const std::uint8_t ADD = 0x6;
const std::uint8_t MUL = 0x7;
const std::uint8_t DIV = 0x8;
const std::uint8_t OR = 0x9;
const std::uint8_t AND = 0xA;
const std::uint8_t XOR = 0xB;
}  // namespace opcodes

namespace types {
const std::uint8_t ADDR = 0;
const std::uint8_t VAL = 1;
}  // namespace types

namespace sizes {
const std::uint8_t BYTE = 0;
const std::uint8_t WORD = 1;
const std::uint8_t DWORD = 2;
const std::uint8_t QWORD = 3;
};

#pragma pack(push, 1)
struct Instruction {
  union {
    std::uint8_t opcode : 4;
    struct {
      std::uint8_t : 4;
      bool extended : 1;
    } flags;
    struct {
      std::uint8_t : 8;
      union {
        struct {
          bool offset : 1;
          std::uint8_t size : 2;
          std::uint8_t type : 1;
          std::uint8_t : 4;
        } second;
        struct {
          std::uint8_t : 4;
          bool offset : 1;
          std::uint8_t size : 2;
          std::uint8_t type : 1;
        } first;
      } operands;
    };
  };

  Instruction(
    std::uint8_t opcode = opcodes::NOP,
    std::uint8_t type1 = types::ADDR,
    std::uint8_t size1 = sizes::BYTE,
    bool offset1 = false,
    std::uint8_t type2 = types::ADDR,
    std::uint8_t size2 = sizes::BYTE,
    bool offset2 = false,
    bool extended = false
  )
  {
    this->opcode = opcode;
    this->flags.extended = extended;
    operands.first.type = type1;
    operands.first.size = size1;
    if (type1 == types::ADDR) operands.first.offset = offset1;

    operands.second.type = type2;
    operands.second.size = size2;
    if (type2 == types::ADDR) operands.second.offset = offset2;
  }

  operator std::uint16_t() {
    return opcode
      | (flags.extended << 4)
      | (operands.second.offset << 8)
      | (operands.second.size << 9)
      | (operands.second.type << 11)
      | (operands.first.offset << 12)
      | (operands.first.size << 13)
      | (operands.first.type << 15);
  }
};
#pragma pack(pop)
}  // namespace instructions
}  // namespace lowvm

#endif
