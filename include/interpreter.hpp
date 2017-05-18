#ifndef INCLUDE_INTERPRETER_HPP_
#define INCLUDE_INTERPRETER_HPP_

#include <service.hpp>

namespace lowvm {
class Interpreter : public StepOnInterface {
 public:
  void stepOn(lowvm::VM* context);
};
}  // namespace lowvm

#endif  // INCLUDE_INTERPRETER_HPP_
