#ifndef ISA_H
#define ISA_H

#include "cstdint"

namespace lowvm {
  using addr = long;
  using cell = std::int32_t;

  namespace instructions {
    const cell mem = 0;
    const cell val = 1;

    const cell nop  = 0x0;
    const cell _mov = 0x1;
    const cell _add = 0x2;
    const cell _mul = 0x3;
    const cell _div = 0x4;
    const cell _or  = 0x5;
    const cell _and = 0x6;
    const cell _xor = 0x7;
    const cell _jmp = 0x8;
    const cell _jz  = 0x9;
    const cell _int = 0xA;
    const cell hlt  = 0xB;

    const cell movvm = _mov xor ((val << 31) bitor (mem << 30));
    const cell movmm = _mov xor ((mem << 31) bitor (mem << 30));
    const cell addvm = _add xor ((val << 31) bitor (mem << 30));
    const cell addmm = _add xor ((mem << 31) bitor (mem << 30));
    const cell mulvm = _mul xor ((val << 31) bitor (mem << 30));
    const cell mulmm = _mul xor ((mem << 31) bitor (mem << 30));
    const cell divvm = _div xor ((val << 31) bitor (mem << 30));
    const cell divmm = _div xor ((mem << 31) bitor (mem << 30));
    const cell orvm  = _or  xor ((val << 31) bitor (mem << 30));
    const cell ormm  = _or  xor ((mem << 31) bitor (mem << 30));
    const cell andvm = _and xor ((val << 31) bitor (mem << 30));
    const cell andmm = _and xor ((mem << 31) bitor (mem << 30));
    const cell xorvm = _xor xor ((val << 31) bitor (mem << 30));
    const cell xormm = _xor xor ((mem << 31) bitor (mem << 30));
    const cell jmpv  = _jmp xor  (val << 31);
    const cell jmpm  = _jmp xor  (mem << 31);
    const cell jzmv  = _jz  xor ((mem << 31) bitor (val << 30));
    const cell jzmm  = _jz  xor ((mem << 31) bitor (mem << 30));
    const cell intv  = _int xor  (val << 31);
    const cell intm  = _int xor  (mem << 31);
  }
}

#endif
