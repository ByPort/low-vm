#ifndef INCLUDE_MEMORY_HPP_
#define INCLUDE_MEMORY_HPP_

#include <vector>

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

class MU : public ServeInterface {
  cell* memory;
  std::vector<SegRecord> active_segments;

  addr abs(addr virtual_address, int seg = 0);

 public:
  MU(cell* pointer, size length);

  cell* getPointer();
  size getLength();
  cell& operator[] (addr at);
  void serve(VM* context, addr header);
};
}  // namespace lowvm

#endif  // INCLUDE_MEMORY_HPP_
