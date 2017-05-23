#ifndef INCLUDE_MEMORY_HPP_
#define INCLUDE_MEMORY_HPP_

#include <vector>

#include <isa.hpp>
#include <service.hpp>

namespace lowvm {
class MU : public ServeInterface {
  struct PageRecord {
    addr self;
    addr* begin;
    size* length;
    cell* flags;

    PageRecord(addr self, addr* begin, size* length, cell* flags)
      : self(self)
      , begin(begin)
      , length(length)
      , flags(flags)
    {}
  };

  cell* memory;
  size length;
  PageRecord* active_page = nullptr;

  addr abs(addr virtual_address);

 public:
  MU(cell* pointer, size length);

  cell* getPointer();
  size getLength();
  cell& at(addr adr);
  addr getActivePageRecordAddr();
  void disablePage();
  //cell& operator[] (addr at);
  void serve(VM* context, addr header);
};
}  // namespace lowvm

#endif  // INCLUDE_MEMORY_HPP_
