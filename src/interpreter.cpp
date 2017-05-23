#include <stdexcept>

#include <interpreter.hpp>
#include <isa.hpp>
#include <vm.hpp>
#include <memory.hpp>

bool lowvm::Interpreter::exec(lowvm::VM* ctx) {
  using I = instructions::Instructions;
  using O = instructions::Opcodes;

  MU& mu = *ctx->getMU();

  try {
    switch (ctx->arg(0)) {
      case c(I::MOVVV): {
        mu[ctx->arg(2)] = ctx->arg(1);
        ctx->ip() += 3;
        break;
      }
      case c(I::MOVAV): {
        mu[ctx->arg(2)] = mu[ctx->arg(1)];
        ctx->ip() += 3;
        break;
      }
      case c(I::MOVVA): {
        mu[mu[ctx->arg(2)]] = ctx->arg(1);
        ctx->ip() += 3;
        break;
      }
      case c(I::MOVAA): {
        mu[mu[ctx->arg(2)]] = mu[ctx->arg(1)];
        ctx->ip() += 3;
        break;
      }
      case c(I::ADDVV): {
        mu[ctx->arg(2)] += ctx->arg(1);
        ctx->ip() += 3;
        break;
      }
      case c(I::ADDAV): {
        mu[ctx->arg(2)] += mu[ctx->arg(1)];
        ctx->ip() += 3;
        break;
      }
      case c(I::ADDAA): {
        mu[mu[ctx->arg(2)]] += mu[ctx->arg(1)];
        ctx->ip() += 3;
        break;
      }
      case c(I::ADDVA): {
        mu[mu[ctx->arg(2)]] += ctx->arg(1);
        ctx->ip() += 3;
        break;
      }
      case c(I::MULVV): {
        mu[ctx->arg(2)] *= ctx->arg(1);
        ctx->ip() += 3;
        break;
      }
      case c(I::MULAV): {
        mu[ctx->arg(2)] *= mu[ctx->arg(1)];
        ctx->ip() += 3;
        break;
      }
      case c(I::DIVVV): {
        if (ctx->arg(1) == 0) {
          ctx->interrupt(Interrupts::DIVIDE_BY_ZERO);
          break;
        }
        mu[ctx->arg(2)] /= ctx->arg(1);
        ctx->ip() += 3;
        break;
      }
      case c(I::DIVAV): {
        if (mu[ctx->arg(1)]) {
          ctx->interrupt(Interrupts::DIVIDE_BY_ZERO);
          break;
        }
        mu[ctx->arg(2)] /= mu[ctx->arg(1)];
        ctx->ip() += 3;
        break;
      }
      case c(I::ORVV): {
        mu[ctx->arg(2)] |= ctx->arg(1);
        ctx->ip() += 3;
        break;
      }
      case c(I::ORAV): {
        mu[ctx->arg(2)] |= mu[ctx->arg(1)];
        ctx->ip() += 3;
        break;
      }
      case c(I::ANDVV): {
        mu[ctx->arg(2)] &= ctx->arg(1);
        ctx->ip() += 3;
        break;
      }
      case c(I::ANDAV): {
        mu[ctx->arg(2)] &= mu[ctx->arg(1)];
        ctx->ip() += 3;
        break;
      }
      case c(I::XORVV): {
        mu[ctx->arg(2)] ^= ctx->arg(1);
        ctx->ip() += 3;
        break;
      }
      case c(I::XORAV): {
        mu[ctx->arg(2)] ^= mu[ctx->arg(1)];
        ctx->ip() += 3;
        break;
      }
      case c(I::JMPV): {
        ctx->ip() = ctx->arg(1);
        break;
      }
      case c(I::JMPA): {
        ctx->ip() = mu[ctx->arg(1)];
        break;
      }
      case c(O::HLT): {
        ctx->halt();
        ctx->ip() += 1;
        break;
      }
      case c(O::NOP): {
        ctx->ip() += 1;
        break;
      }
      case c(I::JZVA): {
        if (mu[mu[ctx->arg(2)]] == 0)
          ctx->ip() = ctx->arg(1);
        else
          ctx->ip() += 3;
        break;
      }
      case c(I::JZAA): {
        if (mu[mu[ctx->arg(2)]] == 0)
          ctx->ip() = mu[ctx->arg(1)];
        else
          ctx->ip() += 3;
        break;
      }
      case c(I::JZVV): {
        if (mu[ctx->arg(2)] == 0)
          ctx->ip() = ctx->arg(1);
        else
          ctx->ip() += 3;
        break;
      }
      case c(I::JZAV): {
        if (mu[ctx->arg(2)] == 0)
          ctx->ip() = mu[ctx->arg(1)];
        else
          ctx->ip() += 3;
        break;
      }
      case c(I::SRVV): {
        try {
          Service* service = ctx->getServices<ServeInterface>()
            .at(mu[ctx->arg(1)]);
          dynamic_cast<ServeInterface*>(service)
            ->serve(ctx, ctx->arg(1));
          ctx->ip() += 2;
        } catch (const std::out_of_range& e) {
          ctx->interrupt(lowvm::Interrupts::INVALID_SERVICE);
        }
        break;
      }
      case c(I::SRVA): {
        try {
          Service* service = ctx->getServices<ServeInterface>()
            .at(mu[mu[ctx->arg(1)]]);
          dynamic_cast<ServeInterface*>(service)
            ->serve(ctx, mu[ctx->arg(1)]);
          ctx->ip() += 2;
        } catch (const std::out_of_range& e) {
          ctx->interrupt(lowvm::Interrupts::INVALID_SERVICE);
        }
        break;
      }
      default: {
        return false;
      }
    }
  } catch (const std::out_of_range& e) {
    ctx->interrupt(Interrupts::BAD_MEMORY_ACCESS);
  }
  return true;
}
