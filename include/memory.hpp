#ifndef MEMORY_H
#define MEMORY_H

#include <vector>

#include "isa.hpp"

namespace lowvm {
struct SegRecord {
  addr begin;
  size length;
  cell flags;

  SegRecord(addr begin, size length, cell flags)
    : begin(begin)
    , length(length)
    , flags(flags)
  {}
};

class MU {
 public:
  MU(cell*& pointer, size length);

  cell* getPointer();
  size getLength();
  cell& operator[] (addr at);
  void service(addr service_header);

 private:
  cell*& memory;
  std::vector<SegRecord> active_segments;

  addr abs(addr virtual_address, int seg = 0);
};
}  // namespace lowvm

#endif
