#include <isa.hpp>

namespace lowvm {
class Service {
 public:
  virtual void operator()(addr service_header) = 0;
};
}  // namespace lowvm
