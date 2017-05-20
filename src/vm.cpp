#include <iostream>
#include <typeinfo>
#include <typeindex>
#include <iterator>

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

void lowvm::VM::interrupt(lowvm::Interrupts iid) {
  addr base;
  addr intlist;
  cell intnum;
  for (
    base = (*memory_unit)[4],
    intlist = 0,
    intnum = static_cast<std::uint32_t>(iid);
    (*memory_unit)[base + intlist] != 0 && intnum > 0;
    ++intlist, --intnum
  ) {
    if (intlist == 7) {
      base = (*memory_unit)[base + intlist];
      intlist = 0;
    }
  }
  if ((*memory_unit)[base + intlist] == 0) throw;
  (*memory_unit)[(*memory_unit)[2]] = (*memory_unit)[1];
  (*memory_unit)[1] = (*memory_unit)[(*memory_unit)[base + intlist]];
}

void lowvm::VM::step() {
  for (
    auto i = services[std::type_index(typeid(StepOnInterface))].begin();
    i != services[std::type_index(typeid(StepOnInterface))].end();
    i++
  ) {
    dynamic_cast<StepOnInterface*>(i->second)->stepOn(
      this,
      std::distance(
        services[std::type_index(typeid(StepOnInterface))].begin(),
        i));
  }
  for (
    auto i = services[std::type_index(typeid(StepOffInterface))].begin();
    i != services[std::type_index(typeid(StepOffInterface))].end();
    i++
  ) {
    dynamic_cast<StepOffInterface*>(i->second)->stepOff(
      this,
      std::distance(
        services[std::type_index(typeid(StepOffInterface))].begin(),
        i));
  }
}
