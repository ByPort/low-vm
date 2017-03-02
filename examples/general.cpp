#include <iostream>
#include <iomanip>
#include <cstdio>

#include "isa.hpp"
#include "vm.hpp"
#include "memory.hpp"

int main() {
  using namespace lowvm::instructions;
  lowvm::cell memory[] = {
    jmpv, 3,
    0,
    movvm, 12, 7,
    jmpv, -1,
    -1, -1, -1, -1,
    intv, 16,
    jmpv, 18,
    2, 'h',
    movvm, 'e', 17,
    intv, 16,
    movvm, 'l', 17,
    intv, 16,
    intv, 16,
    movvm, 'e', 17,
    intv, 16,
    hlt
  };
  lowvm::VM vm;
  lowvm::Memory memoryUnit;
  vm.setMemory(&memoryUnit);
  vm.getMemory().setPointer(memory);
  vm.getMemory().setLength(sizeof(memory) / sizeof(lowvm::cell));
  vm.setService(2, [&](lowvm::cell addr){
    std::cout << "OUT: " << (char)vm.getMemory()[addr+1] << std::endl;
  });
  std::cout << std::hex;
  do {
    std::cout << " IP: " << std::setfill('0') << std::setw(8) << vm.getIP() << std::endl << "COM: " << std::setfill('0') << std::setw(8) << vm.getMemory()[vm.getIP()] << std::endl;
    std::cout << "MEM: " << std::endl;
    for (int i = 0; i < vm.getMemory().getLength(); i++) {
      if (i % 4 == 0)
        std::cout << std::setfill('0') << std::setw(8) << i << " : ";
      std::cout << std::setfill('0') << std::setw(8) << vm.getMemory()[i] << " ";
      if (i % 4 == 3)
        std::cout << std::endl;
    }
    vm.step();
    std::cout << std::endl;
  } while (!vm.isHalted());
  std::cout << "HALTED" << std::endl;
}
