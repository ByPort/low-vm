#include <iostream>
#include <iomanip>
#include <cstdio>

#include "isa.hpp"
#include "vm.hpp"
#include "memory.hpp"

int main() {
  using namespace lowvm::instructions;

  lowvm::cell memory[32] = {
    0xffffffff,
    4,
    31,
    0xffffffff,
    movmm, 1, 2,
    addvm, 8, 2,
    jmpv, 13,  // p1
    hlt,
    addvv, (lowvm::cell)-1, 2,  // p1
    intv, 26,
    addvv, 1, 2,
    movmv, 2, 25,
    jmpm, 0xffffffff,
    0,
  };
  lowvm::cell* memptr = memory;

  lowvm::MU memory_unit(memptr, sizeof(memory) / sizeof(memory[0]));
  lowvm::VM vm(memory_unit);

  std::cout << std::hex;
  do {
    std::cout << " IP: " << std::setw(8) << std::setfill('0')
    << vm.getIP() << std::endl
    << "COM: " << std::setw(8) << std::setfill('0')
    << memory_unit[vm.getIP()] << std::endl;
    std::cout << "MEM: " << std::endl;
    for (lowvm::addr i = 0; i < memory_unit.getLength(); i++) {
      if (i % 4 == 0)
        std::cout << std::setfill('0') << std::setw(8) << i << " : ";
      std::cout << std::setfill('0') << std::setw(8)
      << memory_unit[i] << " ";
      if (i % 4 == 3)
        std::cout << std::endl;
    }
    vm.step();
    std::getchar();
  } while (!vm.isHalted());
  std::cout << "HALTED" << std::endl;
}
