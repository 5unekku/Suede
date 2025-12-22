# Default Types

Suede provides C-like primitive types with modern enhancements for safety and expressiveness.

## Type Categories

### Integer Types

Signed types:
- `sbyte` (8-bit)
- `short` (16-bit)
- `int` (32-bit)
- `long` (64-bit)
- `huge` (128-bit)

Unsigned types:
- `byte` (8-bit)
- `ushort` (16-bit)
- `uint` (32-bit)
- `ulong` (64-bit)
- `uhuge` (128-bit)

### Floating Point Types

- `float` (32-bit)
- `double` (64-bit)
- `quad` (128-bit)

### Other Types

- `bool` (boolean)
- `char` (character)
- `dec` (precise decimal number)

## Type Properties

All default types possess compile-time constant properties:

- `size`: Returns the size in bytes (syntactic alternative to `sizeof(type)`)

These properties are compile-time constants and cannot be modified.

## Immutability

Variables are mutable by default. The `!` suffix marks a variable as immutable, preventing reassignment after initialization. This is separate from readonly (immutable after assignment) and constants (compile time).

Note: `string` is immutable by nature, so reassignment creates a new string and frees the old one. Modifying in place (like indices) does not create a new string. Use `string[n]` for mutable strings (errors on oversized input).

## Example Usage

```c++
// type properties
print(int.size);    // 4
print(double.size); // 8

// immutability
int! constant = 42;
int mut = 10;
mutable = 20;     // ok
constant = 50; // compile error

// type usage
uint count = 100;
float pi = 3.14159;
bool isValid = true;
bool isReallyValid = (bool) 1; // non-zero values cast to true, zero casts to false
```