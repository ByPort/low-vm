#include <typeinfo>
#include <typeindex>

#include <isa.hpp>
#include <vm.hpp>
#include <memory.hpp>
#include <interpreter.hpp>
#include <debugger.hpp>

int main() {
  using I = lowvm::instructions::Instructions;
  using O = lowvm::instructions::Opcodes;
  using lowvm::c;

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
    c(I::SRVV), 23,
    c(O::HLT),
    0, 0, 28, 80, 0xffffffff,
    0xffffffff,
    8,
    79,
    0xffffffff,
    0, 0, 0, 0,
    c(I::MOVAA), 1, 2,
    c(I::ADDVA), 8, 2,
    c(I::JMPV), 17,
    c(O::HLT),
    c(I::ADDVV), (lowvm::cell)-1, 2,
    c(O::NOP),
    c(O::NOP),
    c(I::MOVVA), (lowvm::cell)-70, 2,
    c(I::ADDAA), 2, 2,
    c(I::JZVA), 39, 2,
    c(I::MOVAA), 1, 2,
    c(I::ADDVA), 8, 2,
    c(I::JMPV), 17,
    c(I::ADDVV), 1, 2,
    c(I::MOVAV), 2, 46,
    c(I::JMPA), 0xffffffff,
  };

  lowvm::MU memory_unit(memory, sizeof(memory) / sizeof(memory[0]));
  lowvm::VM vm(&memory_unit);
  lowvm::Interpreter interpreter;
  lowvm::Debugger debugger;

  vm.setService<lowvm::StepOnInterface>(0, &debugger);
  vm.setService<lowvm::StepOffInterface>(0, &debugger);
  vm.setService<lowvm::HaltInterface>(0, &debugger);
  vm.setService<lowvm::InstructionSetProvider>(0, &interpreter);
  vm.setService<lowvm::ServeInterface>(0, &memory_unit);

  do { vm.step(); } while (!vm.isHalted());
}
