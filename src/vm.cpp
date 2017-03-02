#include "vm.hpp"
#include "isa.hpp"
#include "memory.hpp"

lowvm::cell lowvm::VM::arg(lowvm::size number)
{
  return (*memory)[ip + number];
}

bool lowvm::VM::isHalted()
{
  return halted;
}

void lowvm::VM::incIP(lowvm::size offset)
{
  ip += offset;
}
void lowvm::VM::setIP(lowvm::addr ip)
{
  this->ip = ip;
}

void lowvm::VM::setMemory(lowvm::Memory* memory)
{
  this->memory = memory;
}

lowvm::Memory& lowvm::VM::getMemory()
{
  return *memory;
}

void lowvm::VM::setService(lowvm::cell sid, std::function<void(lowvm::addr)> service)
{
  services[sid] = service;
}

lowvm::addr lowvm::VM::getIP()
{
  return ip;
}

void lowvm::VM::step()
{
  using namespace lowvm::instructions;
  switch (arg(0)) {
    case movvm: {
      (*memory)[arg(2)] = arg(1);
      incIP(3);
      break;
    }
    case movmm: {
      (*memory)[arg(2)] = (*memory)[arg(1)];
      incIP(3);
      break;
    }
    case addvm: {
      (*memory)[arg(2)] += arg(1);
      incIP(3);
      break;
    }
    case addmm: {
      (*memory)[arg(2)] += (*memory)[arg(1)];
      incIP(3);
      break;
    }
    case mulvm: {
      (*memory)[arg(2)] *= arg(1);
      incIP(3);
      break;
    }
    case mulmm: {
      (*memory)[arg(2)] *= (*memory)[arg(1)];
      incIP(3);
      break;
    }
    case divvm: {
      (*memory)[arg(2)] /= arg(1);
      incIP(3);
      break;
    }
    case divmm: {
      (*memory)[arg(2)] /= (*memory)[arg(1)];
      incIP(3);
      break;
    }
    case orvm: {
      (*memory)[arg(2)] |= arg(1);
      incIP(3);
      break;
    }
    case ormm: {
      (*memory)[arg(2)] |= (*memory)[arg(1)];
      incIP(3);
      break;
    }
    case andvm: {
      (*memory)[arg(2)] &= arg(1);
      incIP(3);
      break;
    }
    case andmm: {
      (*memory)[arg(2)] &= (*memory)[arg(1)];
      incIP(3);
      break;
    }
    case xorvm: {
      (*memory)[arg(2)] ^= arg(1);
      incIP(3);
      break;
    }
    case xormm: {
      (*memory)[arg(2)] ^= (*memory)[arg(1)];
      incIP(3);
      break;
    }
    case jmpv: {
      ip = arg(1);
      break;
    }
    case jmpm: {
      ip = (*memory)[arg(1)];
      break;
    }
    case hlt: {
      halted = true;
      incIP(1);
      break;
    }
    case nop: {
      incIP(1);
      break;
    }
    case jzmv: {
      if ((*memory)[arg(1)] == 0) ip = arg(2);
      else incIP(3);
      break;
    }
    case jzmm: {
      if ((*memory)[arg(1)] == 0) ip = (*memory)[arg(2)];
      else incIP(3);
      break;
    }
    case intv: {
      services[(*memory)[arg(1)]](arg(1));
      incIP(2);
      break;
    }
  }
}
