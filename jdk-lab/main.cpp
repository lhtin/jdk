#include <iostream>
#include "test.hpp"

int main() {
  std::cout << "HeapWordSize: " << HeapWordSize << std::endl;
  std::cout << "LogHeapWordSize: " << LogHeapWordSize << std::endl;
  std::cout << "heap_word_size(4): " << heap_word_size(4) << std::endl;
  std::cout << "heap_word_size(8): " << heap_word_size(8) << std::endl;
  std::cout << "heap_word_size(9): " << heap_word_size(9) << std::endl;
  std::cout << "pointer_delta(11, 10): " << pointer_delta((HeapWord*)11, (HeapWord*)10) << std::endl;
  std::cout << "pointer_delta(18, 10): " << pointer_delta((HeapWord*)18, (HeapWord*)10) << std::endl;
  std::cout << "pointer_delta(20, 10): " << pointer_delta((HeapWord*)20, (HeapWord*)10) << std::endl;
  return 0;
}
