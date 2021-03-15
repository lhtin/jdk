// An opaque type, so that HeapWord* can be a generic pointer into the heap.
// We require that object sizes be measured in units of heap words (e.g.
// pointer-sized values), so that given HeapWord* hw,
//   hw += oop(hw)->foo();
// works, where foo is a method (like size or scavenge) that returns the
// object size.
class HeapWordImpl;             // Opaque, never defined.
typedef HeapWordImpl* HeapWord; /// HeapWord为堆内存的最小单位

// HeapWordSize must be 2^LogHeapWordSize.
const int HeapWordSize        = sizeof(HeapWord);
#ifdef _LP64
const int LogHeapWordSize     = 3;
#else
const int LogHeapWordSize     = 2;
#endif

// The minimum number of native machine words necessary to contain "byte_size"
// bytes.
inline size_t heap_word_size(size_t byte_size) {
  return (byte_size + (HeapWordSize-1)) >> LogHeapWordSize;
}

// Pointer subtraction.
// The idea here is to avoid ptrdiff_t（C++11中的指针运算的类型）, which is signed and so doesn't have
// the range we might need to find differences from one end of the heap
// to the other.
// A typical use might be:
//     if (pointer_delta(end(), top()) >= size) {
//       // enough room for an object of size
//       ...
// and then additions like
//       ... top() + size ...
// are safe because we know that top() is at least size below end().
inline size_t pointer_delta(const volatile void* left,
                            const volatile void* right,
                            size_t element_size) {
  return (((uintptr_t) left) - ((uintptr_t) right)) / element_size;
}

// A version specialized for HeapWord*'s.
/// 计算两个指针之间相差多少个HeapWord
inline size_t pointer_delta(const HeapWord* left, const HeapWord* right) {
  return pointer_delta(left, right, sizeof(HeapWord));
}
