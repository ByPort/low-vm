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

class ServeInterface : virtual public Service {
 public:
  virtual void serve(VM* context, addr header) = 0;
};

class AttachInterface : virtual public Service {
 public:
  virtual void attach(VM* context, int sid) = 0;
};

class HaltInterface : virtual public Service {
 public:
  virtual void halt(VM* context) = 0;
};

class StepOnInterface : virtual public Service {
 public:
  virtual void stepOn(VM* context, int index) = 0;
};

class StepOffInterface : virtual public Service {
 public:
  virtual void stepOff(VM* context, int index) = 0;
};

class PortInterface : virtual public Service {
 public:
  virtual void recieve(VM* context, cell data) = 0;
  virtual cell send(VM* context) = 0;
};
}  // namespace lowvm

#endif  // INCLUDE_SERVICE_HPP_
