#include <typeinfo>
#include <typeindex>

#include <isa.hpp>
#include <vm.hpp>
#include <memory.hpp>
#include <interpreter.hpp>
#include <debugger.hpp>
#include <io.hpp>

int main() {
  using I = lowvm::instructions::Instructions;
  using O = lowvm::instructions::Opcodes;
  using lowvm::c;

  lowvm::cell memory[64] = {
    0xffffffff,
    8,
    63,
    0xffffffff,
    12,
    0xffffffff,
    0xffffffff,
    0xffffffff,
    c(I::MOVVA), 11, 100,
    c(O::HLT),
    0xffffffff, 0xffffffff, 0xffffffff, 17, 0,
    21, 0xffffffff, 0xffffffff, 0xffffffff,
    c(I::SRVV), 24,
    c(O::HLT),
    1, 1, 'e', 'r', 'r', 'o', 'r', ':', ' ', 'b', 'a', 'd', ' ', 'm', 'e', 'm', 'o', 'r', 'y', '\n', '\0',
  };

  lowvm::MU memory_unit(memory, sizeof(memory) / sizeof(memory[0]));
  lowvm::VM vm(&memory_unit);
  lowvm::Interpreter interpreter;
  lowvm::Debugger debugger;
  lowvm::IO io;

  vm.setService<lowvm::StepOnInterface>(0, &debugger);
  vm.setService<lowvm::HaltInterface>(0, &debugger);
  vm.setService<lowvm::InstructionSetProvider>(0, &interpreter);
  vm.setService<lowvm::ServeInterface>(0, &memory_unit);
  vm.setService<lowvm::ServeInterface>(1, &io);

  do { vm.step(); } while (!vm.isHalted());
}
