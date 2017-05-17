#include <sstream>
#include <stdexcept>

#include <vm.hpp>
#include <isa.hpp>
#include <memory.hpp>
#include <service.hpp>

lowvm::VM::VM(MU& memory_unit)
  : memory_unit(memory_unit)
{
  setService(0, &memory_unit);
}

lowvm::MU& lowvm::VM::getMU() {
  return memory_unit;
}

lowvm::cell& lowvm::VM::arg(size number) {
  return memory_unit[ip() + number];
}

lowvm::addr lowvm::VM::getIP() {
  return ip();
}

lowvm::addr& lowvm::VM::ip() {
  return memory_unit[1];
}

lowvm::addr& lowvm::VM::sp() {
  return memory_unit[2];
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
    case movvv: {
      memory_unit[arg(2)] = arg(1);
      ip() += 3;
      break;
    }
    case movmv: {
      memory_unit[arg(2)] = memory_unit[arg(1)];
      ip() += 3;
      break;
    }
    case movvm: {
      memory_unit[memory_unit[arg(2)]] = arg(1);
      ip() += 3;
      break;
    }
    case movmm: {
      memory_unit[memory_unit[arg(2)]] = memory_unit[arg(1)];
      ip() += 3;
      break;
    }
    case addvv: {
      memory_unit[arg(2)] += arg(1);
      ip() += 3;
      break;
    }
    case addmv: {
      memory_unit[arg(2)] += memory_unit[arg(1)];
      ip() += 3;
      break;
    }
    case addmm: {
      memory_unit[memory_unit[arg(2)]] += memory_unit[arg(1)];
      ip() += 3;
      break;
    }
    case addvm: {
      memory_unit[memory_unit[arg(2)]] += arg(1);
      ip() += 3;
      break;
    }
    case mulvv: {
      memory_unit[arg(2)] *= arg(1);
      ip() += 3;
      break;
    }
    case mulmv: {
      memory_unit[arg(2)] *= memory_unit[arg(1)];
      ip() += 3;
      break;
    }
    case divvv: {
      memory_unit[arg(2)] /= arg(1);
      ip() += 3;
      break;
    }
    case divmv: {
      memory_unit[arg(2)] /= memory_unit[arg(1)];
      ip() += 3;
      break;
    }
    case orvv: {
      memory_unit[arg(2)] |= arg(1);
      ip() += 3;
      break;
    }
    case ormv: {
      memory_unit[arg(2)] |= memory_unit[arg(1)];
      ip() += 3;
      break;
    }
    case andvv: {
      memory_unit[arg(2)] &= arg(1);
      ip() += 3;
      break;
    }
    case andmv: {
      memory_unit[arg(2)] &= memory_unit[arg(1)];
      ip() += 3;
      break;
    }
    case xorvv: {
      memory_unit[arg(2)] ^= arg(1);
      ip() += 3;
      break;
    }
    case xormv: {
      memory_unit[arg(2)] ^= memory_unit[arg(1)];
      ip() += 3;
      break;
    }
    case jmpv: {
      ip() = arg(1);
      break;
    }
    case jmpm: {
      ip() = memory_unit[arg(1)];
      break;
    }
    case hlt: {
      halted = true;
      ip() += 1;
      break;
    }
    case nop: {
      ip() += 1;
      break;
    }
    case jzvm: {
      if (memory_unit[memory_unit[arg(2)]] == 0)
        ip() = arg(1);
      else
        ip() += 3;
      break;
    }
    case jzmm: {
      if (memory_unit[memory_unit[arg(2)]] == 0)
        ip() = memory_unit[arg(1)];
      else
        ip() += 3;
      break;
    }
    case jzvv: {
      if (memory_unit[arg(2)] == 0)
        ip() = arg(1);
      else
        ip() += 3;
      break;
    }
    case jzmv: {
      if (memory_unit[arg(2)] == 0)
        ip() = memory_unit[arg(1)];
      else
        ip() += 3;
      break;
    }
    case intv: {
      (*services[memory_unit[arg(1)]])(arg(1));
      ip() += 2;
      break;
    }
    case intm: {
      (*services[memory_unit[memory_unit[arg(1)]]])(memory_unit[arg(1)]);
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
