#include <iostream>
#include <string>
#include <algorithm>

#include <io.hpp>
#include <memory.hpp>

void lowvm::IO::serve(lowvm::VM* context, lowvm::addr header) {
  switch (context->getMU()->at(header + 1)) {
    case 0: {
      std::cout << static_cast<char>(context->getMU()->at(header + 2));
      break;
    }
    case 1: {
      for (
        lowvm::addr i = header + 2;
        static_cast<char>(context->getMU()->at(i)) != '\0';
        i++
      ) {
        std::cout << static_cast<char>(context->getMU()->at(i));
      }
      break;
    }
    case 2: {
      char ch;
      std::cin >> ch;
      context->getMU()->at(header + 2) = ch;
      break;
    }
    case 3: {
      std::string s;
      std::cin >> s;
      std::copy(
        s.begin(),
        s.begin() + context->getMU()->at(header + 2),
        &context->getMU()->at(header + 3));
    }
  }
}
