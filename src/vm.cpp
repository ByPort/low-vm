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
  return memory_unit->at(ip() + number);
}

void lowvm::VM::halt() {
  halted = true;
  for (
    auto i = services[std::type_index(typeid(HaltInterface))].begin();
    i != services[std::type_index(typeid(HaltInterface))].end();
    i++
  ) {
    dynamic_cast<HaltInterface*>(i->second)->halt(this);
  }
}

lowvm::addr lowvm::VM::getIP() {
  return ip();
}

lowvm::addr& lowvm::VM::ip() {
  return memory_unit->at(a(MainAddresses::IP));
}

lowvm::addr& lowvm::VM::sp() {
  return memory_unit->at(a(MainAddresses::SP));
}

bool lowvm::VM::isHalted() {
  return halted;
}

void lowvm::VM::interrupt(lowvm::Interrupts iid) {
  addr ip = memory_unit->at(a(MainAddresses::IP));
  addr pageRecordAddr = memory_unit->getActivePageRecordAddr();
  memory_unit->disablePage();
  addr base;
  addr intlist;
  cell intnum;
  for (
    base = memory_unit->at(4),
    intlist = 0,
    intnum = static_cast<std::uint32_t>(iid);
    intnum > 0;
    ++intlist, --intnum
  ) {
    if (intlist == 7) {
      base = memory_unit->at(base + intlist);
      intlist = 0;
    }
  }
  memory_unit->at(memory_unit->at(a(MainAddresses::SP))) = ip;
  memory_unit->at(a(MainAddresses::SP))--;
  memory_unit->at(memory_unit->at(a(MainAddresses::SP))) = pageRecordAddr;
  memory_unit->at(a(MainAddresses::IP)) = memory_unit->at(memory_unit->at(base + intlist));
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
  {
    auto i = getServices<InstructionSetProvider>().begin();
    for (;
      !dynamic_cast<InstructionSetProvider*>(i->second)->exec(this) &&
      i != getServices<InstructionSetProvider>().end();
      i++) continue;
    if (i == getServices<InstructionSetProvider>().end()) {
      interrupt(Interrupts::INVALID_INSTRUCTION);
    }
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
