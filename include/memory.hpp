#ifndef MEMORY_H
#define MEMORY_H

#include <cstdint>
#include <vector>

#include <isa.hpp>
#include <service.hpp>
#include <vm.hpp>

namespace lowvm {
struct SegRecord {
  addr begin;
  size length;
  std::uint8_t flags;

  SegRecord(addr begin, size length, std::uint8_t flags)
    : begin(begin)
    , length(length)
    , flags(flags)
  {}
};

class MU : public Service {
 public:
  MU(ptr& pointer, size length);

  ptr getPointer();
  size getLength();
  template <typename T>
  T& at(addr adr, bool alignment = false);
  void operator()(VM& context, addr service_header);

 private:
  ptr& memory;
  std::vector<SegRecord> active_segments;

  addr abs(addr virtual_address, int seg = 0);
};
}  // namespace lowvm

#endif
