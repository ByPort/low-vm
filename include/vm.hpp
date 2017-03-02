#ifndef VM_H
#define VM_H

#include <functional>
#include <map>

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
    std::map<lowvm::cell, std::function<void(lowvm::addr)>> services;

    lowvm::cell arg(lowvm::size number);

  public:
    void step();
    bool isHalted();
    void incIP(lowvm::size offset);
    void setIP(lowvm::addr ip);
    void setMemory(Memory* memory);
    Memory& getMemory();
  };
}

#endif
