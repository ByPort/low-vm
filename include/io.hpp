#ifndef INCLUDE_IO_HPP_
#define  INCLUDE_IO_HPP_

#include <service.hpp>
#include <vm.hpp>
#include <isa.hpp>

namespace lowvm {
class IO : public ServeInterface {
 public:
  void serve(VM* context, addr header);
};
}  // namespace lowvm

#endif  // INCLUDE_IO_HPP_
