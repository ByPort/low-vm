#include <iostream>
#include <iomanip>
#include <stdexcept>

#include <debugger.hpp>
#include <isa.hpp>
#include <vm.hpp>
#include <memory.hpp>

void lowvm::Debugger::stepOn(lowvm::VM* context, int index) {
  std::clog << std::hex;
  std::clog << " IP: " << std::setw(8) << std::setfill('0')
  << context->getIP() << '\n'
  << "COM: " << std::setw(8) << std::setfill('0')
  << context->getMU()->at(context->getIP()) << '\n';
  std::clog << "MEM: " << '\n';
  for (lowvm::addr i = 0; i < (*context->getMU()).getLength(); i++) {
    if (i % 4 == 0)
      std::clog << std::setfill('0') << std::setw(8) << i << " : ";
    std::clog << std::setfill('0') << std::setw(8)
    << context->getMU()->at(i) << " ";
    if (i % 4 == 3)
      std::clog << '\n';
  }
  std::clog << std::dec;
}

void lowvm::Debugger::stepOff(lowvm::VM* context, int index) {
  std::getchar();
}

void lowvm::Debugger::halt(lowvm::VM* context) {
  std::clog << "HALTED" << '\n';
}
