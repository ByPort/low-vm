#ifndef INCLUDE_SERVICE_HPP_
#define INCLUDE_SERVICE_HPP_

#include <isa.hpp>
#include <vm.hpp>

namespace lowvm {
class Service {
 public:
  virtual void interrupt(lowvm::VM* context, addr service_header) = 0;
  virtual void attach(lowvm::VM* context) = 0;
  virtual void stepOn(lowvm::VM* context) = 0;
  virtual void stepOff(lowvm::VM* context) = 0;
  virtual void halt(lowvm::VM* context) = 0;
};
}  // namespace lowvm

#endif  // INCLUDE_SERVICE_HPP_
