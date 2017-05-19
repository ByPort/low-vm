#ifndef INCLUDE_DEBUGGER_HPP_
#define INCLUDE_DEBUGGER_HPP_

#include <service.hpp>

namespace lowvm {
class Debugger : public StepOnInterface, public StepOffInterface, public HaltInterface {
 public:
  void stepOn(lowvm::VM* context, int index);
  void stepOff(lowvm::VM* context, int index);
  void halt(lowvm::VM* context);
};
}  // namespace lowvm

#endif  // INCLUDE_DEBUGGER_HPP_
