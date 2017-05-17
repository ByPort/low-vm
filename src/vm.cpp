#include <sstream>
#include <stdexcept>
#include <cmath>

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

lowvm::instructions::Instruction& lowvm::VM::currentInstruction() {
  return *static_cast<lowvm::instructions::Instruction*>(static_cast<void*>(&memory_unit.at<std::uint16_t>(ip())));
}

std::uint64_t lowvm::VM::arg(size number) {
  switch (number) {
    case 0: return !currentInstruction().flags.extended
      ? static_cast<std::uint16_t>(currentInstruction())
      : *static_cast<std::uint32_t*>(static_cast<ptr>(&currentInstruction()));
    case 1: switch (currentInstruction().operands.first.size) {
      case 0: return *static_cast<std::uint8_t*>(
        static_cast<ptr>(&currentInstruction()) +
        (!currentInstruction().flags.extended ? 2 : 4)
      );
      case 1: return *static_cast<std::uint16_t*>(
        static_cast<ptr>(&currentInstruction()) +
        (!currentInstruction().flags.extended ? 2 : 4)
      );
      case 2: return *static_cast<std::uint32_t*>(
        static_cast<ptr>(&currentInstruction()) +
        (!currentInstruction().flags.extended ? 2 : 4)
      );
      case 3: return *static_cast<std::uint64_t*>(
        static_cast<ptr>(&currentInstruction()) +
        (!currentInstruction().flags.extended ? 2 : 4)
      );
    }
    case 2: switch (currentInstruction().operands.second.size) {
      case 0: return *static_cast<std::uint8_t*>(
        static_cast<ptr>(&currentInstruction()) +
        (!currentInstruction().flags.extended ? 2 : 4) +
        static_cast<std::uint32_t>(std::pow(2, currentInstruction().operands.first.size))
      );
      case 1: return *static_cast<std::uint16_t*>(
        static_cast<ptr>(&currentInstruction()) +
        (!currentInstruction().flags.extended ? 2 : 4) +
        static_cast<std::uint32_t>(std::pow(2, currentInstruction().operands.first.size))
      );
      case 2: return *static_cast<std::uint32_t*>(
        static_cast<ptr>(&currentInstruction()) +
        (!currentInstruction().flags.extended ? 2 : 4) +
        static_cast<std::uint32_t>(std::pow(2, currentInstruction().operands.first.size))
      );
      case 3: return *static_cast<std::uint64_t*>(
        static_cast<ptr>(&currentInstruction()) +
        (!currentInstruction().flags.extended ? 2 : 4) +
        static_cast<uint32_t>(std::pow(2, currentInstruction().operands.first.size))
      );
    }
  }
}

lowvm::addr lowvm::VM::getIP() {
  return ip();
}

lowvm::addr& lowvm::VM::ip() {
  return memory_unit.at<lowvm::addr>(1, true);
}

lowvm::addr& lowvm::VM::sp() {
  return memory_unit.at<lowvm::addr>(2, true);
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
      switch (currentInstruction().operands.first.size) {
        case 0: {
          memory_unit.at<std::uint8_t>(arg(2)) = static_cast<std::uint8_t>(arg(1));
          break;
        }
        case 1: {
          memory_unit.at<std::uint16_t>(arg(2)) = static_cast<std::uint16_t>(arg(1));
          break;
        }
        case 2: {
          memory_unit.at<std::uint32_t>(arg(2)) = static_cast<std::uint32_t>(arg(1));
          break;
        }
        case 3: {
          memory_unit.at<std::uint64_t>(arg(2)) = static_cast<std::uint64_t>(arg(1));
          break;
        }
      }
      ip() += currentInstruction.totalSize();
      break; // TODO(byport): here
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
