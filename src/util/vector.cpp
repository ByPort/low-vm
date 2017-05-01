#include <util/vector.hpp>

template <typename T>
void lowvm::util::vector<T>::push_back(T&& value) {
  data = realloc(data, sizeof(T) * ++count);
  data[count - 1] = value;
}

template <typename T>
T& lowvm::util::vector<T>::back() {
  return data[count - 1];
}

template <typename T>
size_t lowvm::util::vector<T>::size() {
  return count;
}

template <typename T>
T& lowvm::util::vector<T>::operator[](size_t index) {
  return data[index];
}
