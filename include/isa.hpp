#ifndef ISA_H
#define ISA_H

#include "cstdint"

namespace lowvm {
  using addr = std::int32_t;
  using size = addr;
  using cell = std::int32_t;

  namespace instructions {
    const lowvm::cell mem = 0;
    const lowvm::cell val = 1;

    const lowvm::cell nop  = 0x0;
    const lowvm::cell _mov = 0x1;
    const lowvm::cell _add = 0x2;
    const lowvm::cell _mul = 0x3;
    const lowvm::cell _div = 0x4;
    const lowvm::cell _or  = 0x5;
    const lowvm::cell _and = 0x6;
    const lowvm::cell _xor = 0x7;
    const lowvm::cell _jmp = 0x8;
    const lowvm::cell _jz  = 0x9;
    const lowvm::cell _int = 0xA;
    const lowvm::cell hlt  = 0xB;

    const lowvm::cell movvm = _mov xor ((val << 31) bitor (mem << 30));
    const lowvm::cell movmm = _mov xor ((mem << 31) bitor (mem << 30));
    const lowvm::cell addvm = _add xor ((val << 31) bitor (mem << 30));
    const lowvm::cell addmm = _add xor ((mem << 31) bitor (mem << 30));
    const lowvm::cell mulvm = _mul xor ((val << 31) bitor (mem << 30));
    const lowvm::cell mulmm = _mul xor ((mem << 31) bitor (mem << 30));
    const lowvm::cell divvm = _div xor ((val << 31) bitor (mem << 30));
    const lowvm::cell divmm = _div xor ((mem << 31) bitor (mem << 30));
    const lowvm::cell orvm  = _or  xor ((val << 31) bitor (mem << 30));
    const lowvm::cell ormm  = _or  xor ((mem << 31) bitor (mem << 30));
    const lowvm::cell andvm = _and xor ((val << 31) bitor (mem << 30));
    const lowvm::cell andmm = _and xor ((mem << 31) bitor (mem << 30));
    const lowvm::cell xorvm = _xor xor ((val << 31) bitor (mem << 30));
    const lowvm::cell xormm = _xor xor ((mem << 31) bitor (mem << 30));
    const lowvm::cell jmpv  = _jmp xor  (val << 31);
    const lowvm::cell jmpm  = _jmp xor  (mem << 31);
    const lowvm::cell jzmv  = _jz  xor ((mem << 31) bitor (val << 30));
    const lowvm::cell jzmm  = _jz  xor ((mem << 31) bitor (mem << 30));
    const lowvm::cell intv  = _int xor  (val << 31);
    const lowvm::cell intm  = _int xor  (mem << 31);
  }
}

#endif
