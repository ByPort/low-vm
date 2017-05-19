#include <iostream>
#include <typeinfo>
#include <typeindex>

#include <vm.hpp>
#include <isa.hpp>
#include <memory.hpp>
#include <service.hpp>

lowvm::VM::VM() {}

lowvm::VM::VM(MU* memory_unit)
  : memory_unit(memory_unit) {}

lowvm::MU* lowvm::VM::getMU() {
  return memory_unit;
}

lowvm::cell& lowvm::VM::arg(size number) {
  return (*memory_unit)[ip() + number];
}

void lowvm::VM::halt() {
  halted = true;
  for (auto i = services[std::type_index(typeid(HaltInterface))].begin(); i != services[std::type_index(typeid(HaltInterface))].end(); i++) {
    dynamic_cast<HaltInterface*>(i->second)->halt(this);
  }
}

std::map<std::type_index, std::map<int, lowvm::Service*>>& lowvm::VM::getServices() {
  return services;
}

lowvm::addr lowvm::VM::getIP() {
  return ip();
}

lowvm::addr& lowvm::VM::ip() {
  return (*memory_unit)[1];
}

lowvm::addr& lowvm::VM::sp() {
  return (*memory_unit)[2];
}

bool lowvm::VM::isHalted() {
  return halted;
}

void lowvm::VM::setService(std::type_index serviceType, int sid, lowvm::Service* service) {
  if (AttachInterface* attachable = dynamic_cast<AttachInterface*>(service)) {
    attachable->attach(this);
  }
  if (services[serviceType].find(sid) != services[serviceType].end())
    throw std::invalid_argument(
      "Service with SID " + std::to_string(sid) + " already exists");
  services[serviceType][sid] = service;
}

void lowvm::VM::step() {
  for (auto i = services[std::type_index(typeid(StepOnInterface))].begin(); i != services[std::type_index(typeid(StepOnInterface))].end(); i++) {
    dynamic_cast<StepOnInterface*>(i->second)->stepOn(this);
  }
  for (auto i = services[std::type_index(typeid(StepOffInterface))].begin(); i != services[std::type_index(typeid(StepOffInterface))].end(); i++) {
    dynamic_cast<StepOffInterface*>(i->second)->stepOff(this);
  }
}
