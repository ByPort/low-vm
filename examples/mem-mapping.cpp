#include <typeinfo>
#include <typeindex>

#include <isa.hpp>
#include <vm.hpp>
#include <memory.hpp>
#include <interpreter.hpp>
#include <debugger.hpp>

int main() {
  using namespace lowvm::instructions;

  lowvm::cell memory[200] = {
    0xffffffff,
    20,
    199,
    8,
    0, 0, 0, 0,
    16,
    0, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
    26,
    80,
    0xffffffff,
    0xffffffff,
    INTV, 23,
    HLT,
    0, 0, 0,
    0xffffffff,
    8,
    79,
    0xffffffff,
    0, 0, 0, 0,
    MOVAA, 1, 2,
    ADDVA, 8, 2,
    JMPV, 17,
    HLT,
    ADDVV, (lowvm::cell)-1, 2,
    NOP,
    NOP,
    MOVVA, (lowvm::cell)-70, 2,
    ADDAA, 2, 2,
    JZVA, 39, 2,
    MOVAA, 1, 2,
    ADDVA, 8, 2,
    JMPV, 17,
    ADDVV, 1, 2,
    MOVAV, 2, 46,
    JMPA, 0xffffffff,
  };

  lowvm::MU memory_unit(memory, sizeof(memory) / sizeof(memory[0]));
  lowvm::VM vm(&memory_unit);
  lowvm::Interpreter interpreter;
  lowvm::Debugger debugger;

  vm.setService(std::type_index(typeid(lowvm::StepOnInterface)), 0, &debugger);
  vm.setService(std::type_index(typeid(lowvm::StepOffInterface)), 0, &debugger);
  vm.setService(std::type_index(typeid(lowvm::HaltInterface)), 0, &debugger);
  vm.setService(std::type_index(typeid(lowvm::StepOnInterface)), 1, &interpreter);
  vm.setService(std::type_index(typeid(lowvm::InterruptInterface)), 0, &memory_unit);

  do { vm.step(); } while (!vm.isHalted());
}
