#ifndef MEMORY_H
#define MEMORY_H

#include "isa.hpp"

namespace lowvm {
  class Memory {
  private:
    cell* memory = nullptr;
    long length = 0;
  public:
    void setPointer(lowvm::cell*);
    lowvm::cell* getPointer();
    void setLength(long);
    long getLength();
    lowvm::cell operator [] (addr);
  };
}

#endif
