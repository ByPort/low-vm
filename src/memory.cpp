#include "memory.hpp"
#include "isa.hpp"

void lowvm::Memory::setPointer(lowvm::cell* pointer)
{
  memory = pointer;
}

lowvm::cell* lowvm::Memory::getPointer()
{
  return memory;
}

void lowvm::Memory::setLength(lowvm::size length)
{
  this->length = length;
}

lowvm::size lowvm::Memory::getLength()
{
  return length;
}

lowvm::cell lowvm::Memory::operator [] (lowvm::addr at)
{
  return memory[at];
}
