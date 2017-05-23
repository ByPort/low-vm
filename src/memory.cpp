#include <stdexcept>

#include <memory.hpp>
#include <isa.hpp>
#include <vm.hpp>

lowvm::MU::MU(cell* pointer, size length)
  : memory(pointer)
  , length(length)
{}

lowvm::cell* lowvm::MU::getPointer() {
  return memory;
}

lowvm::size lowvm::MU::getLength() {
  return active_page? *active_page->length : length;
}

void lowvm::MU::serve(VM* context, addr header) {
  switch (this->at(header + 1)) {
    case 0: {
      active_page = new PageRecord(
        this->at(header + 2),
        static_cast<addr*>(&this->at(header + 2)),
        static_cast<size*>(&this->at(header + 3)),
        &this->at(header + 4));
      this->at(a(MainAddresses::IP)) -= 2;  // TODO(byport): retardical
      break;
    }
    case 1: {
      this->at(header + 2) = getLength();
      break;
    }
  }
}

lowvm::cell& lowvm::MU::at(addr adr) {
  if (adr >= getLength())
    throw std::out_of_range("Address is smaller than size");
  return memory[abs(adr)];
}

lowvm::addr lowvm::MU::abs(addr virtual_address) {
  return (active_page ? *active_page->begin : 0) + virtual_address;
}

lowvm::addr lowvm::MU::getActivePageRecordAddr() {
  if (!active_page) return 0;
  return active_page->self;
}

void lowvm::MU::disablePage() {
  if (active_page) delete active_page;
  active_page = nullptr;
}
