#include <iostream>

#include "isa.hpp"
#include "vm.hpp"
#include "memory.hpp"

int main() {
  using namespace lowvm::instructions;
  long memory[] = {
    hlt, hlt
  };
  lowvm::VM<lowvm::Memory> vm;
  vm.getMemory().setPointer(memory);
  vm.getMemory().setLength(sizeof(memory) / sizeof(long));
  do { vm.step(); } while (!vm.isHalted());
}
