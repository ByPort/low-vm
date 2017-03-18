#include <iostream>
#include <iomanip>
#include <stdexcept>

#include "memory.hpp"
#include "isa.hpp"

lowvm::MU::MU(cell*& pointer, size length)
  : memory(pointer)
  , length(length)
{
  std::clog << "MU: created" << std::endl;
}

lowvm::cell* lowvm::MU::getPointer() {
  return memory;
}

lowvm::size lowvm::MU::getLength() {
  return length;
}

void lowvm::MU::service(addr service_header) {
  std::cout << "MU: oh hi there!" << std::endl;
}

lowvm::cell& lowvm::MU::operator[] (addr at) {
  if (at >= length) throw std::out_of_range("Address is smaller than size");
  // std::clog << "MU: Accessing to "
  // << std::hex << std::setw(8) << std::setfill('0')
  // << at
  // << " (=0x" << memory[at] << ")" << std::endl;
  return memory[at];
}
