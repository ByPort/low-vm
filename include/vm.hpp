#ifndef VM_H
#define VM_H

#include "isa.hpp"
#include "memory.hpp"

namespace lowvm {
  template <typename MemoryType>
  class VM
  {
  private:
    bool halted = false;
    addr ip = 0;
    long vmid = 0x10101010;
    MemoryType memory;

    long arg(long number)
    {
      return memory[ip + number];
    }

  public:
    void step()
    {
      using namespace lowvm::instructions;
      switch (arg(0)) {
        case hlt: {
          halted = true;
          break;
        }
      }
    }

    bool isHalted()
    {
      return halted;
    }

    void incIP(long offset)
    {
      ip += offset;
    }
    void setIP(addr ip)
    {
      this->ip = ip;
    }

    MemoryType& getMemory()
    {
      return memory;
    }
  };
}

#endif
