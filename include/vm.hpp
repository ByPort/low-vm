#ifndef VM_H
#define VM_H

#include <functional>

#include "isa.hpp"
#include "memory.hpp"

namespace lowvm {
  class VM
  {
  private:
    bool halted = false;
    lowvm::addr ip = 0;
    lowvm::cell vmid = 0x10101010;
    Memory* memory = nullptr;

    lowvm::cell arg(long number);

  public:
    void step();
    bool isHalted();
    void incIP(long offset);
    void setIP(lowvm::addr ip);
    void setMemory(Memory* memory);
    Memory& getMemory();
  };
}

#endif
