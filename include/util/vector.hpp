#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>

namespace lowvm::util {
template <typename T>
class vector {
  T* data = nullptr;
  size_t count = 0;

 public:
  void push_back(T&& value);
  T& back();
  size_t size();
  T& operator[](size_t index);
};
}  // namespace lowvm::util

#endif
