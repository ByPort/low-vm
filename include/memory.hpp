#ifndef MEMORY_H
#define MEMORY_H

#if defined(__AVR__) || defined(DEBUG_UTIL)
#include <util/vector.hpp>
using lowvm::util::vector;
#else
#include <vector>
using std::vector;
#endif

#include <isa.hpp>
#include <service.hpp>

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

class MU : public Service {
 public:
  MU(cell*& pointer, size length);

  cell* getPointer();
  size getLength();
  cell& operator[] (addr at);
  void operator()(addr service_header);

 private:
  cell*& memory;
  vector<SegRecord> active_segments;

  addr abs_addr(addr virtual_address, int seg = 0);
};
}  // namespace lowvm

#endif
