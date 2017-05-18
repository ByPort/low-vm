#include <sstream>
#include <stdexcept>

#include <interpreter.hpp>
#include <isa.hpp>
#include <vm.hpp>
#include <memory.hpp>

void lowvm::Interpreter::stepOn(lowvm::VM* c) {
  using namespace lowvm::instructions;

  switch (c->arg(0)) {
    case MOVVV: {
      (*c->getMU())[c->arg(2)] = c->arg(1);
      c->ip() += 3;
      break;
    }
    case MOVAV: {
      (*c->getMU())[c->arg(2)] = (*c->getMU())[c->arg(1)];
      c->ip() += 3;
      break;
    }
    case MOVVA: {
      (*c->getMU())[(*c->getMU())[c->arg(2)]] = c->arg(1);
      c->ip() += 3;
      break;
    }
    case MOVAA: {
      (*c->getMU())[(*c->getMU())[c->arg(2)]] = (*c->getMU())[c->arg(1)];
      c->ip() += 3;
      break;
    }
    case ADDVV: {
      (*c->getMU())[c->arg(2)] += c->arg(1);
      c->ip() += 3;
      break;
    }
    case ADDAV: {
      (*c->getMU())[c->arg(2)] += (*c->getMU())[c->arg(1)];
      c->ip() += 3;
      break;
    }
    case ADDAA: {
      (*c->getMU())[(*c->getMU())[c->arg(2)]] += (*c->getMU())[c->arg(1)];
      c->ip() += 3;
      break;
    }
    case ADDVA: {
      (*c->getMU())[(*c->getMU())[c->arg(2)]] += c->arg(1);
      c->ip() += 3;
      break;
    }
    case MULVV: {
      (*c->getMU())[c->arg(2)] *= c->arg(1);
      c->ip() += 3;
      break;
    }
    case MULAV: {
      (*c->getMU())[c->arg(2)] *= (*c->getMU())[c->arg(1)];
      c->ip() += 3;
      break;
    }
    case DIVVV: {
      (*c->getMU())[c->arg(2)] /= c->arg(1);
      c->ip() += 3;
      break;
    }
    case DIVAV: {
      (*c->getMU())[c->arg(2)] /= (*c->getMU())[c->arg(1)];
      c->ip() += 3;
      break;
    }
    case ORVV: {
      (*c->getMU())[c->arg(2)] |= c->arg(1);
      c->ip() += 3;
      break;
    }
    case ORAV: {
      (*c->getMU())[c->arg(2)] |= (*c->getMU())[c->arg(1)];
      c->ip() += 3;
      break;
    }
    case ANDVV: {
      (*c->getMU())[c->arg(2)] &= c->arg(1);
      c->ip() += 3;
      break;
    }
    case ANDAV: {
      (*c->getMU())[c->arg(2)] &= (*c->getMU())[c->arg(1)];
      c->ip() += 3;
      break;
    }
    case XORVV: {
      (*c->getMU())[c->arg(2)] ^= c->arg(1);
      c->ip() += 3;
      break;
    }
    case XORAV: {
      (*c->getMU())[c->arg(2)] ^= (*c->getMU())[c->arg(1)];
      c->ip() += 3;
      break;
    }
    case JMPV: {
      c->ip() = c->arg(1);
      break;
    }
    case JMPA: {
      c->ip() = (*c->getMU())[c->arg(1)];
      break;
    }
    case HLT: {
      c->halt();
      c->ip() += 1;
      break;
    }
    case NOP: {
      c->ip() += 1;
      break;
    }
    case JZVA: {
      if ((*c->getMU())[(*c->getMU())[c->arg(2)]] == 0)
        c->ip() = c->arg(1);
      else
        c->ip() += 3;
      break;
    }
    case JZAA: {
      if ((*c->getMU())[(*c->getMU())[c->arg(2)]] == 0)
        c->ip() = (*c->getMU())[c->arg(1)];
      else
        c->ip() += 3;
      break;
    }
    case JZVV: {
      if ((*c->getMU())[c->arg(2)] == 0)
        c->ip() = c->arg(1);
      else
        c->ip() += 3;
      break;
    }
    case JZAV: {
      if ((*c->getMU())[c->arg(2)] == 0)
        c->ip() = (*c->getMU())[c->arg(1)];
      else
        c->ip() += 3;
      break;
    }
    case INTV: {
      dynamic_cast<InterruptInterface*>(c->getServices()[std::type_index(typeid(InterruptInterface))][(*c->getMU())[c->arg(1)]])->interrupt(c, c->arg(1));
      c->ip() += 2;
      break;
    }
    case INTA: {
      dynamic_cast<InterruptInterface*>(c->getServices()[std::type_index(typeid(InterruptInterface))][(*c->getMU())[(*c->getMU())[c->arg(1)]]])->interrupt(c, (*c->getMU())[c->arg(1)]);
      c->ip() += 2;
      break;
    }
    default: {
      std::stringstream msg;
      msg << "No instruction with code " << c->arg(0);
      throw std::invalid_argument(msg.str());
    }
  }
}
