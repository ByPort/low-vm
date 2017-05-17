#ifndef ISA_H
#define ISA_H

#include "cstdint"

namespace lowvm {
using addr = std::uint32_t;
using virt = addr;
using size = std::uint32_t;
using cell = std::uint32_t;

namespace instructions {
const std::uint32_t mem = 0;
const std::uint32_t val = 1;

const cell nop = 0x0;
const cell hlt = 0x1;
const cell itr = 0x2;

const cell jmp = 0x3;
const cell jz  = 0x4;

const cell mov = 0x5;

const cell add = 0x6;
const cell mul = 0x7;
const cell div = 0x8;

const cell lor  = 0x9;
const cell land = 0xA;
const cell lxor = 0xB;

constexpr cell i(cell instruction = nop, std::uint32_t first = mem, std::uint32_t second = mem) {
  return instruction | (first << 31) | (second << 30);
}

const cell intv = i(itr, val);  // Interrupt with header at farg addr
const cell intm = i(itr, mem);  // Interrupt with header at addr contains at farg addr

const cell jmpv = i(jmp, val);  // Jump to farg addr
const cell jmpm = i(jmp, mem);  // Jump to addr contains at farg addr
const cell jzvm = i(jz, val);  // Jump to farg addr if value at addr contains at sarg addr = 0
const cell jzmm = i(jz, mem);  // Jump to addr contains at farg addr if value at addr contains at sarg addr = 0
const cell jzvv = i(jz, val, val);  // Jump to farg addr if value contains at sarg addr = 0
const cell jzmv = i(jz, mem, val);  // Jump to addr contains at farg addr if value contains at sarg addr = 0

const cell movvm = i(mov, val);  // Move farg value to addr contains at sarg addr
const cell movmm = i(mov, mem);  // Move value contains at farg addr to addr contains at sarg addr
const cell movvv = i(mov, val, val);  // Move farg value to sarg addr
const cell movmv = i(mov, mem, val);  // Move value contains in farg addr to sarg addr

const cell addvm = i(add, val);  // Add farg value to value contains at sarg addr and move res to addr contains at sarg addr
const cell addmm = i(add, mem);  // Add value contains at farg addr to value contains at sarg addr and move res to addr contains at sarg addr
const cell addvv = i(add, val, val);  // Add farg value to value at sarg addr and move res to sarg addr
const cell addmv = i(add, mem, val);  // Add value contains at farg addr to value at sarg addr and move res to sarg addr
const cell mulvm = i(mul, val);  // Multiply farg value and value contains at sarg addr and move res to addr contains at sarg addr
const cell mulmm = i(mul, mem);  // Multiply value contains at farg addr and value contains at sarg addr and move res to addr contains at sarg addr
const cell mulvv = i(mul, val, val);  // Multiply farg value and value at sarg addr and move res to sarg addr
const cell mulmv = i(mul, mem, val);  // Multiply value contains at farg addr and value at sarg addr and move res to sarg addr
const cell divvm = i(div, val);
const cell divmm = i(div, mem);
const cell divvv = i(div, val, val);
const cell divmv = i(div, mem, val);

const cell orvm = i(lor, val);
const cell ormm = i(lor, mem);
const cell orvv = i(lor, val, val);
const cell ormv = i(lor, mem, val);
const cell andvm = i(land, val);
const cell andmm = i(land, mem);
const cell andvv = i(land, val, val);
const cell andmv = i(land, mem, val);
const cell xorvm = i(lxor, val);
const cell xormm = i(lxor, mem);
const cell xorvv = i(lxor, val, val);
const cell xormv = i(lxor, mem, val);
}  // namespace instructions
}  // namespace lowvm

#endif
