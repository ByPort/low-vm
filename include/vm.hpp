#ifndef INCLUDE_VM_HPP_
#define INCLUDE_VM_HPP_

#include <map>
#include <typeindex>

#include <isa.hpp>
// #include <memory.hpp>
// #include <service.hpp>

namespace lowvm {
class Service;
class MU;

class VM {
  std::map<std::type_index, std::map<int, Service*>> services;
  bool halted = false;
  MU* memory_unit;

 public:
  VM();
  explicit VM(MU* memory_unit);

  void step();
  addr getIP();
  MU* getMU();
  std::map<std::type_index, std::map<int, Service*>>& getServices();
  void setService(std::type_index serviceType, int sid, Service* service);
  void setMU(MU* memory_unit);
  bool isHalted();
  void halt();
  cell& arg(size number);
  addr& ip();
  addr& sp();
};
}  // namespace lowvm

#endif  // INCLUDE_VM_HPP_
