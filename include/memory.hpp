#ifndef MEMORY_H
#define MEMORY_H

#include <functional>

#include "isa.hpp"

namespace lowvm {
class MU {
 public:
  MU(cell*& pointer, size length);

  cell* getPointer();
  size getLength();
  cell& operator[] (addr at);
  void service(addr service_header);

 private:
  cell*& memory;
  size length;
};
}  // namespace lowvm

#endif
