#include <sstream>
#include <stdexcept>

#include <vm.hpp>
#include <isa.hpp>
#include <memory.hpp>
#include <service.hpp>

lowvm::VM::VM() {}

lowvm::VM::VM(MU* memory_unit)
  : memory_unit(memory_unit) {
  setService(0, memory_unit);
}

lowvm::MU& lowvm::VM::getMU() {
  return *memory_unit;
}

lowvm::cell& lowvm::VM::arg(size number) {
  return (*memory_unit)[ip() + number];
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

void lowvm::VM::setService(int sid, lowvm::Service* service) {
  if (services.find(sid) != services.end())
    throw std::invalid_argument(
      "Service with SID " + std::to_string(sid) + " already exists");
  services[sid] = service;
}

void lowvm::VM::step() {
  using namespace lowvm::instructions;

  switch (arg(0)) {
    case MOVVV: {
      (*memory_unit)[arg(2)] = arg(1);
      ip() += 3;
      break;
    }
    case MOVAV: {
      (*memory_unit)[arg(2)] = (*memory_unit)[arg(1)];
      ip() += 3;
      break;
    }
    case MOVVA: {
      (*memory_unit)[(*memory_unit)[arg(2)]] = arg(1);
      ip() += 3;
      break;
    }
    case MOVAA: {
      (*memory_unit)[(*memory_unit)[arg(2)]] = (*memory_unit)[arg(1)];
      ip() += 3;
      break;
    }
    case ADDVV: {
      (*memory_unit)[arg(2)] += arg(1);
      ip() += 3;
      break;
    }
    case ADDAV: {
      (*memory_unit)[arg(2)] += (*memory_unit)[arg(1)];
      ip() += 3;
      break;
    }
    case ADDAA: {
      (*memory_unit)[(*memory_unit)[arg(2)]] += (*memory_unit)[arg(1)];
      ip() += 3;
      break;
    }
    case ADDVA: {
      (*memory_unit)[(*memory_unit)[arg(2)]] += arg(1);
      ip() += 3;
      break;
    }
    case MULVV: {
      (*memory_unit)[arg(2)] *= arg(1);
      ip() += 3;
      break;
    }
    case MULAV: {
      (*memory_unit)[arg(2)] *= (*memory_unit)[arg(1)];
      ip() += 3;
      break;
    }
    case DIVVV: {
      (*memory_unit)[arg(2)] /= arg(1);
      ip() += 3;
      break;
    }
    case DIVAV: {
      (*memory_unit)[arg(2)] /= (*memory_unit)[arg(1)];
      ip() += 3;
      break;
    }
    case ORVV: {
      (*memory_unit)[arg(2)] |= arg(1);
      ip() += 3;
      break;
    }
    case ORAV: {
      (*memory_unit)[arg(2)] |= (*memory_unit)[arg(1)];
      ip() += 3;
      break;
    }
    case ANDVV: {
      (*memory_unit)[arg(2)] &= arg(1);
      ip() += 3;
      break;
    }
    case ANDAV: {
      (*memory_unit)[arg(2)] &= (*memory_unit)[arg(1)];
      ip() += 3;
      break;
    }
    case XORVV: {
      (*memory_unit)[arg(2)] ^= arg(1);
      ip() += 3;
      break;
    }
    case XORAV: {
      (*memory_unit)[arg(2)] ^= (*memory_unit)[arg(1)];
      ip() += 3;
      break;
    }
    case JMPV: {
      ip() = arg(1);
      break;
    }
    case JMPA: {
      ip() = (*memory_unit)[arg(1)];
      break;
    }
    case HLT: {
      halted = true;
      ip() += 1;
      break;
    }
    case NOP: {
      ip() += 1;
      break;
    }
    case JZVA: {
      if ((*memory_unit)[(*memory_unit)[arg(2)]] == 0)
        ip() = arg(1);
      else
        ip() += 3;
      break;
    }
    case JZAA: {
      if ((*memory_unit)[(*memory_unit)[arg(2)]] == 0)
        ip() = (*memory_unit)[arg(1)];
      else
        ip() += 3;
      break;
    }
    case JZVV: {
      if ((*memory_unit)[arg(2)] == 0)
        ip() = arg(1);
      else
        ip() += 3;
      break;
    }
    case JZAV: {
      if ((*memory_unit)[arg(2)] == 0)
        ip() = (*memory_unit)[arg(1)];
      else
        ip() += 3;
      break;
    }
    case INTV: {
      services[(*memory_unit)[arg(1)]]->interrupt(this, arg(1));
      ip() += 2;
      break;
    }
    case INTA: {
      services[(*memory_unit)[(*memory_unit)[arg(1)]]]
        ->interrupt(this, (*memory_unit)[arg(1)]);
      ip() += 2;
      break;
    }
    default: {
      std::stringstream msg;
      msg << "No instruction with code " << arg(0);
      throw std::invalid_argument(msg.str());
    }
  }
}
