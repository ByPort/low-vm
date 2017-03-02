#include "memory.hpp"
#include "isa.hpp"

void lowvm::Memory::setPointer(long* pointer)
{
  memory = pointer;
}

long* lowvm::Memory::getPointer()
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

long lowvm::Memory::operator [] (addr at)
{
  return memory[at];
}
