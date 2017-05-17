#include <stdexcept>

#include <memory.hpp>
#include <isa.hpp>

lowvm::MU::MU(ptr& pointer, size length)
  : memory(pointer)
{
  active_segments.push_back(SegRecord(0, length, 0));
}

ptr lowvm::MU::getPointer() {
  return memory;
}

lowvm::size lowvm::MU::getLength() {
  return active_segments.back().length;
}

void lowvm::MU::operator()(lowvm::VM& context, addr service_header) {
  switch (at<std::uint8_t>(service_header)) {
    case 0: {
      addr base;
      addr seglist;
      cell segnum;
      for (
        base = at<std::uint32_t>(3, true),
        seglist = 0,
        segnum = at<std::uint8_t>(service_header + 1);
        at<std::uint32_t>(base + seglist * 4) != 0 && segnum > 0;
        ++seglist, --segnum
      ) {
        if (seglist == 7) {
          base = at<std::uint32_t>(base + seglist * 4);
          seglist = 0;
        }
      }
      if (at<std::uint32_t>(base + seglist * 4) == 0) throw;
      size instruction_size = context.currentInstruction().totalSize();
      active_segments.push_back(SegRecord(
        at<std::uint32_t>(at<std::uint32_t>(base + seglist * 4)),
        at<std::uint32_t>(at<std::uint32_t>(base + seglist * 4) + 4),
        at<std::uint32_t>(at<std::uint32_t>(base + seglist * 4) + 8)
      ));
      context.ip() -= instruction_size;  // TODO(byport): retardical
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

template <typename T>
T& lowvm::MU::at(addr adr, bool alignment) {
  adr *= sizeof(T) * alignment;
  if (adr >= active_segments.back().length)
    throw std::out_of_range("Address is smaller than size");
  // std::clog << "MU: Accessing to "
  // << std::hex << std::setw(8) << std::setfill('0')
  // << at
  // << " (=0x" << memory[abs(at, active_segments.size() - 1)] << ")" << std::endl;
  return *static_cast<T*>(memory + abs(adr, active_segments.size() - 1));
}
