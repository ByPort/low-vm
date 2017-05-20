#include <stdexcept>

#include <interpreter.hpp>
#include <isa.hpp>
#include <vm.hpp>
#include <memory.hpp>

void lowvm::Interpreter::stepOn(lowvm::VM* c, int index) {
  using I = instructions::Instructions;
  using O = instructions::Opcodes;

  switch (c->arg(0)) {
    case c(I::MOVVV): {
      (*c->getMU())[c->arg(2)] = c->arg(1);
      c->ip() += 3;
      break;
    }
    case c(I::MOVAV): {
      (*c->getMU())[c->arg(2)] = (*c->getMU())[c->arg(1)];
      c->ip() += 3;
      break;
    }
    case c(I::MOVVA): {
      (*c->getMU())[(*c->getMU())[c->arg(2)]] = c->arg(1);
      c->ip() += 3;
      break;
    }
    case c(I::MOVAA): {
      (*c->getMU())[(*c->getMU())[c->arg(2)]] = (*c->getMU())[c->arg(1)];
      c->ip() += 3;
      break;
    }
    case c(I::ADDVV): {
      (*c->getMU())[c->arg(2)] += c->arg(1);
      c->ip() += 3;
      break;
    }
    case c(I::ADDAV): {
      (*c->getMU())[c->arg(2)] += (*c->getMU())[c->arg(1)];
      c->ip() += 3;
      break;
    }
    case c(I::ADDAA): {
      (*c->getMU())[(*c->getMU())[c->arg(2)]] += (*c->getMU())[c->arg(1)];
      c->ip() += 3;
      break;
    }
    case c(I::ADDVA): {
      (*c->getMU())[(*c->getMU())[c->arg(2)]] += c->arg(1);
      c->ip() += 3;
      break;
    }
    case c(I::MULVV): {
      (*c->getMU())[c->arg(2)] *= c->arg(1);
      c->ip() += 3;
      break;
    }
    case c(I::MULAV): {
      (*c->getMU())[c->arg(2)] *= (*c->getMU())[c->arg(1)];
      c->ip() += 3;
      break;
    }
    case c(I::DIVVV): {
      (*c->getMU())[c->arg(2)] /= c->arg(1);
      c->ip() += 3;
      break;
    }
    case c(I::DIVAV): {
      (*c->getMU())[c->arg(2)] /= (*c->getMU())[c->arg(1)];
      c->ip() += 3;
      break;
    }
    case c(I::ORVV): {
      (*c->getMU())[c->arg(2)] |= c->arg(1);
      c->ip() += 3;
      break;
    }
    case c(I::ORAV): {
      (*c->getMU())[c->arg(2)] |= (*c->getMU())[c->arg(1)];
      c->ip() += 3;
      break;
    }
    case c(I::ANDVV): {
      (*c->getMU())[c->arg(2)] &= c->arg(1);
      c->ip() += 3;
      break;
    }
    case c(I::ANDAV): {
      (*c->getMU())[c->arg(2)] &= (*c->getMU())[c->arg(1)];
      c->ip() += 3;
      break;
    }
    case c(I::XORVV): {
      (*c->getMU())[c->arg(2)] ^= c->arg(1);
      c->ip() += 3;
      break;
    }
    case c(I::XORAV): {
      (*c->getMU())[c->arg(2)] ^= (*c->getMU())[c->arg(1)];
      c->ip() += 3;
      break;
    }
    case c(I::JMPV): {
      c->ip() = c->arg(1);
      break;
    }
    case c(I::JMPA): {
      c->ip() = (*c->getMU())[c->arg(1)];
      break;
    }
    case c(O::HLT): {
      c->halt();
      c->ip() += 1;
      break;
    }
    case c(O::NOP): {
      c->ip() += 1;
      break;
    }
    case c(I::JZVA): {
      if ((*c->getMU())[(*c->getMU())[c->arg(2)]] == 0)
        c->ip() = c->arg(1);
      else
        c->ip() += 3;
      break;
    }
    case c(I::JZAA): {
      if ((*c->getMU())[(*c->getMU())[c->arg(2)]] == 0)
        c->ip() = (*c->getMU())[c->arg(1)];
      else
        c->ip() += 3;
      break;
    }
    case c(I::JZVV): {
      if ((*c->getMU())[c->arg(2)] == 0)
        c->ip() = c->arg(1);
      else
        c->ip() += 3;
      break;
    }
    case c(I::JZAV): {
      if ((*c->getMU())[c->arg(2)] == 0)
        c->ip() = (*c->getMU())[c->arg(1)];
      else
        c->ip() += 3;
      break;
    }
    case c(I::SRVV): {
      try {
        Service* service = c->getServices()
          [std::type_index(typeid(ServeInterface))]
          .at((*c->getMU())[c->arg(1)]);
        dynamic_cast<ServeInterface*>(service)
          ->serve(c, c->arg(1));
        c->ip() += 2;
      } catch (const std::out_of_range& e) {
        c->interrupt(lowvm::Interrupts::INVALID_SERVICE);
      }
      break;
    }
    case c(I::SRVA): {
      try {
        Service* service = c->getServices()
          [std::type_index(typeid(ServeInterface))]
          .at((*c->getMU())[(*c->getMU())[c->arg(1)]]);
        dynamic_cast<ServeInterface*>(service)
          ->serve(c, (*c->getMU())[c->arg(1)]);
        c->ip() += 2;
      } catch (const std::out_of_range& e) {
        c->interrupt(lowvm::Interrupts::INVALID_SERVICE);
      }
      break;
    }
    default: {
      c->interrupt(lowvm::Interrupts::INVALID_INSTRUCTION);
    }
  }
}
