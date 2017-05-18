#ifndef INCLUDE_SERVICE_HPP_
#define INCLUDE_SERVICE_HPP_

#include <isa.hpp>
// #include <vm.hpp>

namespace lowvm {
class VM;

class Service {
 public:
  virtual ~Service() {}
};

class InterruptInterface : virtual public Service {
 public:
  virtual void interrupt(VM* context, addr service_header) = 0;
};

class AttachInterface : virtual public Service {
 public:
  virtual void attach(VM* context) = 0;
};

class HaltInterface : virtual public Service {
 public:
  virtual void halt(VM* context) = 0;
};

class StepOnInterface : virtual public Service {
 public:
  virtual void stepOn(VM* context) = 0;
};

class StepOffInterface : virtual public Service {
 public:
  virtual void stepOff(VM* context) = 0;
};
}  // namespace lowvm

#endif  // INCLUDE_SERVICE_HPP_
