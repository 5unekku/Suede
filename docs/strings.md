# Strings

Suede provides two string types to balance immutability and performance.

## String Types

The `string` type is immutable and requires assignment. When reassigned, a new string is created rather than modifying the existing one.

The `string[n]` type is mutable with a fixed capacity.

## Properties and Methods

Strings share the same properties and methods as arrays:

- `size`: Memory usage in bytes
- `capacity`: Total character capacity
- `stride`: Size of character type
- `count`: Number of characters (aliased from `std.array.count`)

The method `std.string.count(str)` is aliased to `std.array.count(str)`.

## String Conversion and Interpolation/Formatting

The process of turning non-string types into strings (such as integers, floats, etc.) and how to format them and integrate them into larger strings.

## Example Usage

```c++
// immutable string
string str1 = "Hello, World!";
print(str1.count);  // 13

// fixed-capacity mutable string
string[64] str2 = "Hello, World!";
print(str2.count);     // 13
print(str2.capacity);  // 64
str2[0] = 'h';         // modifies in place

// string reassignment creates new string
string greeting = "Hello";
greeting = "Hi";  // frees old, creates new

// string conversion + formatting
print(2.stringify()); // prints "2", implicit, used for example
print(2.stringify("0x")); // prints "0x00000002"
print((80510.5097).stringify("f2")); // rounded to 2 fixed decimals (80510.51)
print((790.10083).stringify("g2")); // rounded to 2 decimals (790.1)
print((80510.5097).stringify("f2", ' ')); // rounded to 2 fixed decimals, separated by a character of choice (80 510.51)
print((80510.5097):f2(' ')); // same thing, formatting shorthand
```
