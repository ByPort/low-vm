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

void lowvm::Memory::setLength(long length)
{
  this->length = length;
}

long lowvm::Memory::getLength()
{
  return length;
}

lowvm::cell lowvm::Memory::operator [] (addr at)
{
  return memory[at];
}
