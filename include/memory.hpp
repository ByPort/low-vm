#ifndef MEMORY_H
#define MEMORY_H

#include "isa.hpp"

namespace lowvm {
  class Memory {
  private:
    cell* memory = nullptr;
    lowvm::size length = 0;
  public:
    void setPointer(lowvm::cell*);
    lowvm::cell* getPointer();
    void setLength(lowvm::size);
    lowvm::size getLength();
    lowvm::cell& operator [] (lowvm::addr);
  };
}

#endif
