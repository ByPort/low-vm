#ifndef MEMORY_H
#define MEMORY_H

#include "isa.hpp"

namespace lowvm {
  class Memory {
  private:
    long* memory = nullptr;
    long length = 0;
  public:
    void setPointer(long*);
    long* getPointer();
    void setLength(long);
    long getLength();
    long operator [] (addr);
  };
}

#endif
