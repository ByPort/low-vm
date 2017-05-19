#include <stdexcept>

#include <memory.hpp>
#include <isa.hpp>
#include <vm.hpp>

lowvm::MU::MU(cell* pointer, size length)
  : memory(pointer)
{
  active_segments.push_back(SegRecord(0, length, 0));
}

lowvm::cell* lowvm::MU::getPointer() {
  return memory;
}

lowvm::size lowvm::MU::getLength() {
  return active_segments.back().length;
}

void lowvm::MU::serve(VM* context, addr header) {
  switch ((*this)[header + 1]) {
    case 0: {
      addr base;
      addr seglist;
      cell segnum;
      for (
        base = (*this)[3],
        seglist = 0,
        segnum = (*this)[header + 2];
        (*this)[base + seglist] != 0 && segnum > 0;
        ++seglist, --segnum
      ) {
        if (seglist == 7) {
          base = (*this)[base + seglist];
          seglist = 0;
        }
      }
      if ((*this)[base + seglist] == 0) throw;
      active_segments.push_back(SegRecord(
        (*this)[(*this)[base + seglist]],
        (*this)[(*this)[base + seglist] + 1],
        (*this)[(*this)[base + seglist] + 2]
      ));
      (*this)[1] -= 2;  // TODO(byport): retardical
      break;
    }
    case 1: {
      (*this)[header + 2] = active_segments.back().length;
      break;
    }
  }
}

lowvm::addr lowvm::MU::abs(addr virtual_address, int seg) {
  for (
    int i = active_segments.size() - 1;
    i >= static_cast<int>(active_segments.size()) - 1 - seg;
    i--
  ) {
    virtual_address += active_segments[i].begin;
  }
  return virtual_address;
}

lowvm::cell& lowvm::MU::operator[] (addr at) {
  if (at >= active_segments.back().length)
    throw std::out_of_range("Address is smaller than size");
  // std::clog << "MU: Accessing to "
  // << std::hex << std::setw(8) << std::setfill('0')
  // << at
  // << " (=0x" << memory[abs(at, active_segments.size() - 1)] << ")" << std::endl;
  return memory[abs(at, active_segments.size() - 1)];
}
