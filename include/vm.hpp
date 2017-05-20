#ifndef INCLUDE_VM_HPP_
#define INCLUDE_VM_HPP_

#include <map>
#include <typeindex>

#include <isa.hpp>
#include <service.hpp>

namespace lowvm {
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
  template <typename T>
  void setService(int sid, T* service) {
    static_assert(
      std::is_base_of<Service, T>::value,
      "T is not inherited from Service");
    if (services[std::type_index(typeid(T))].count(sid) > 0) {
      throw std::invalid_argument(
        "Service with SID " +
        std::to_string(sid) +
        " already exists");
    }
    services[std::type_index(typeid(T))][sid] = service;
    if (AttachInterface* attachable = dynamic_cast<AttachInterface*>(service)) {
      attachable->attach(this, sid);
    }
  }
  void setMU(MU* memory_unit);
  bool isHalted();
  void halt();
  cell& arg(size number);
  addr& ip();
  addr& sp();
  void interrupt(Interrupts iid);
};
}  // namespace lowvm

#endif  // INCLUDE_VM_HPP_
