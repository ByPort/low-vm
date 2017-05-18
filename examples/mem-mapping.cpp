#include <iostream>
#include <iomanip>
#include <cstdio>

#include "isa.hpp"
#include "vm.hpp"
#include "memory.hpp"

int main() {
  using namespace lowvm::instructions;

  lowvm::cell memory[200] = {
    0xffffffff,
    20,
    199,
    8,
    0, 0, 0, 0,
    16,
    0, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
    25,
    80,
    0xffffffff,
    0xffffffff,
    INTV, 23,
    HLT,
    0, 0,
    0xffffffff,
    8,
    79,
    0xffffffff,
    0, 0, 0, 0,
    MOVAA, 1, 2,
    ADDVA, 8, 2,
    JMPV, 17,
    HLT,
    ADDVV, (lowvm::cell)-1, 2,
    NOP,
    NOP,
    MOVVA, (lowvm::cell)-70, 2,
    ADDAA, 2, 2,
    JZVA, 39, 2,
    MOVAA, 1, 2,
    ADDVA, 8, 2,
    JMPV, 17,
    ADDVV, 1, 2,
    MOVAV, 2, 46,
    JMPA, 0xffffffff,
  };

  lowvm::MU memory_unit(memory, sizeof(memory) / sizeof(memory[0]));
  lowvm::VM vm(&memory_unit);
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
