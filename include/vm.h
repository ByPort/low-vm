#ifndef VM_H
#define VM_H

#include "isa.h"
#include "memory.h"

namespace lowvm {
  class VM
  {
  private:
    bool halted = false;
    addr ip = 0;
    long vmid = 0x10101010;

  public:
    Memory memory;

    void step();
    bool isHalted();
    void incIP(int);
    void setIP(addr);
  };
}

#endif VM_H
