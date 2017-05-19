#ifndef INCLUDE_IO_HPP_
#define  INCLUDE_IO_HPP_

#include <service.hpp>
#include <vm.hpp>
#include <isa.hpp>

namespace lowvm {
class IO : public InterruptInterface {
 public:
  void interrupt(VM* context, addr service_header);
};
}  // namespace lowvm

#endif  // INCLUDE_IO_HPP_
