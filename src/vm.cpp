#include "vm.hpp"
#include "isa.hpp"
#include "memory.hpp"

lowvm::cell lowvm::VM::arg(long number)
{
  return (*memory)[ip + number];
}

bool lowvm::VM::isHalted()
{
  return halted;
}

void lowvm::VM::incIP(long offset)
{
  ip += offset;
}
void lowvm::VM::setIP(lowvm::addr ip)
{
  this->ip = ip;
}

void lowvm::VM::setMemory(lowvm::Memory* memory)
{
  this->memory = memory;
}

lowvm::Memory& lowvm::VM::getMemory()
{
  return *memory;
}

void lowvm::VM::step()
{
  using namespace lowvm::instructions;
  switch (arg(0)) {
    case hlt: {
      halted = true;
      break;
    }
  }
}
