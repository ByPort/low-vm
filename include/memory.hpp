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

class MU : public Service {
  cell* memory;
  std::vector<SegRecord> active_segments;

  addr abs(addr virtual_address, int seg = 0);

 public:
  MU(cell* pointer, size length);

  cell* getPointer();
  size getLength();
  cell& operator[] (addr at);
  void interrupt(VM* context, addr service_header);
  void attach(lowvm::VM* context);
  void stepOn(lowvm::VM* context);
  void stepOff(lowvm::VM* context);
  void halt(lowvm::VM* context);
};
}  // namespace lowvm

#endif  // INCLUDE_MEMORY_HPP_
