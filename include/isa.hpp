#ifndef ISA_H
#define ISA_H

typedef long addr;

namespace lowvm {
  namespace instructions {
    const long mem = 0;
    const long val = 1;

    const long nop  = 0x0;
    const long _mov = 0x1;
    const long _add = 0x2;
    const long _mul = 0x3;
    const long _div = 0x4;
    const long _or  = 0x5;
    const long _and = 0x6;
    const long _xor = 0x7;
    const long _jmp = 0x8;
    const long _jz  = 0x9;
    const long _int = 0xA;
    const long hlt  = 0xB;

    const long movvm = _mov xor ((val << 31) bitor (mem << 30));
    const long movmm = _mov xor ((mem << 31) bitor (mem << 30));
    const long addvm = _add xor ((val << 31) bitor (mem << 30));
    const long addmm = _add xor ((mem << 31) bitor (mem << 30));
    const long mulvm = _mul xor ((val << 31) bitor (mem << 30));
    const long mulmm = _mul xor ((mem << 31) bitor (mem << 30));
    const long divvm = _div xor ((val << 31) bitor (mem << 30));
    const long divmm = _div xor ((mem << 31) bitor (mem << 30));
    const long orvm  = _or  xor ((val << 31) bitor (mem << 30));
    const long ormm  = _or  xor ((mem << 31) bitor (mem << 30));
    const long andvm = _and xor ((val << 31) bitor (mem << 30));
    const long andmm = _and xor ((mem << 31) bitor (mem << 30));
    const long xorvm = _xor xor ((val << 31) bitor (mem << 30));
    const long xormm = _xor xor ((mem << 31) bitor (mem << 30));
    const long jmpv  = _jmp xor  (val << 31);
    const long jmpm  = _jmp xor  (mem << 31);
    const long jzmv  = _jz  xor ((mem << 31) bitor (val << 30));
    const long jzmm  = _jz  xor ((mem << 31) bitor (mem << 30));
    const long intv  = _int xor  (val << 31);
    const long intm  = _int xor  (mem << 31);
  }
}

#endif
