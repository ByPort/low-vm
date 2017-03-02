#include "isa.hpp"
#include "vm.hpp"
#include "memory.hpp"

int main() {
  using namespace lowvm::instructions;
  lowvm::cell memory[] = {
    hlt, hlt
  };
  lowvm::VM vm;
  lowvm::Memory memoryUnit;
  vm.setMemory(&memoryUnit);
  vm.getMemory().setPointer(memory);
  vm.getMemory().setLength(sizeof(memory) / sizeof(lowvm::cell));
  do { vm.step(); } while (!vm.isHalted());
}
