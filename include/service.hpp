#ifndef SERVICE_H
#define SERVICE_H

#include <isa.hpp>
#include <vm.hpp>

namespace lowvm {
class Service {
 public:
  virtual void operator()(lowvm::VM& context, addr service_header) = 0;
};
}  // namespace lowvm

#endif
