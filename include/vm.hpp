#ifndef INCLUDE_VM_HPP_
#define INCLUDE_VM_HPP_

#include <map>

#include <isa.hpp>
#include <memory.hpp>
#include <service.hpp>

namespace lowvm {
class VM {
  std::map<int, Service*> services;
  bool halted = false;
  MU* memory_unit;

  cell& arg(size number);
  addr& ip();
  addr& sp();

 public:
  VM();
  explicit VM(MU* memory_unit);

  void step();
  addr getIP();
  MU& getMU();
  void setService(int sid, Service* service);
  void setMU(MU* memory_unit);
  bool isHalted();
};
}  // namespace lowvm

#endif  // INCLUDE_VM_HPP_
