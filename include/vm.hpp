#ifndef VM_H
#define VM_H

#include <map>

#include <isa.hpp>
#include <memory.hpp>
#include <service.hpp>

namespace lowvm {
class VM {
 public:
  VM(MU& memory_unit);

  void step();
  MU& getMU();
  addr getIP();
  void setService(int sid, Service* service);
  bool isHalted();

 private:
  MU& memory_unit;
  std::map<int, Service*> services;
  bool halted = false;

  cell& arg(size number);
  addr& ip();
  addr& sp();
};
}  // namespace lowvm

#endif
