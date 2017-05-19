#include <iostream>
#include <string>
#include <algorithm>

#include <io.hpp>
#include <memory.hpp>

void lowvm::IO::interrupt(lowvm::VM* context, lowvm::addr service_header) {
  switch ((*context->getMU())[service_header + 1]) {
    case 0: {
      std::cout << static_cast<char>((*context->getMU())[service_header + 2]);
      break;
    }
    case 1: {
      for (lowvm::addr i = service_header + 2; static_cast<char>((*context->getMU())[i]) != '\0'; i++) {
        std::cout << static_cast<char>((*context->getMU())[i]);
      }
      break;
    }
    case 2: {
      char ch;
      std::cin >> ch;
      (*context->getMU())[service_header + 2] = ch;
      break;
    }
    case 3: {
      std::string s;
      std::cin >> s;
      std::copy(s.begin(), s.begin() + (*context->getMU())[service_header + 2], &(*context->getMU())[service_header + 3]);
    }
  }
}
