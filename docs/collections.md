# Collections
## Arrays

Arrays in Suede are immutable containers with mutable contents.

### Array Types

Fixed-capacity arrays are declared with a specific capacity.

Dynamically-allocated arrays are declared without a fixed capacity; size determined at initialization. The array size is fixed after initialization; only the allocation is dynamic. This is identical in performance and code.

### Properties

Arrays provide several compile-time properties:

- `size`: Memory usage in bytes
- `capacity`: Total number of indices
- `stride`: Size of the array's type

### Usage

```c++
// fixed-capacity array
int[8] fixedArray = [ 1, 2, 3, 4 ];
print(fixedArray.count);     // 4
print(fixedArray.capacity);  // 8

// dynamically-allocated array
int[] dynamicArray = [ 1, 2, 3, 4 ];
print(dynamicArray.count);     // 4
print(dynamicArray.capacity);  // 4

// array properties
print(fixedArray.size);   // size in bytes
print(fixedArray.stride); // size of int type

// accessing elements
fixedArray[0] = 10;
int first = fixedArray[0];
```

<!-- ## Vectors  (TODO)-->