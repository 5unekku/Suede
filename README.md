# Suede

Suede is a programming language that serves as a successor to C++, C, and Rust, focused on zero-cost abstractions, quality-of-life improvements, and pretty, easy to read syntax. It is designed to be as safe as Rust, powerful as C++, but more simplistic akin to C (as C++'s abstractions are frequently considered controversial).

Suede is fundamentally a **struct-based language**. Structs encapsulate state and behavior without inheritance or subtyping. This avoids the complexity of class-based inheritance hierarchies while still providing the benefits of organizing data and methods together.

It preserves low-level control while introducing modern language features, emphasizing procedural and functional programming paradigms over an object-oriented approach.

Suede intends to maintain C's capacity for low-level programming, C++'s wide featureset, and Rust's compile-time safe memory management, polished with a clean, modern syntax.

## Specifications
   
### Types

#### 1. Default Types

  - C-like types (`(u)int`,`float`,`bool` etc. + derivatives)
  - Possess minimal properties like `size` (syntactic alternative to `sizeof(type)`), which are compile-time constants and cannot be modified
  - Non-nullable by default, can be forced nullable via `type?` (sentinel value; n amount of checks where n = bits in type). Will default to 0 if not defined


#### 2. Arrays

  - Immutable, contents mutable

   ##### Properties
  - `size` (memory usage in bytes)
  - `capacity` (total indices)
  - `stride` (size of the type of the array (returns type.size); space between the beginnings of indices)
  - `arr.count`

#### 3. Strings

  - `string` is an immutable type that requires assignment
  - `string[n]` is mutable, fixed-capacity.
  - Same properties and methods of Arrays. `std.string.count(str)` aliased to `std.array.count(str)`

#### 4. Structs

  - `struct Name { … }` are user-defined composite types that group related data and behavior. They can be manually created or constructed via struct typedef templates. Deliberately named `struct` (like in C) rather than `class` or `object` to emphasize procedural/functional programming over object-oriented paradigms
  - Can contain fields (data), methods (functions), and properties (like C#)
  - Instances have no runtime header beyond fields
  - Fields: Values of variables inside of structs

##### Fields

  - Allowed
    - Constant values.
  - Disallowed
    - Anything non-constant, requiring more than value fetching. Such values must be calculated via methods.

##### Methods

  - Functions associated with a struct type that can take parameters and operate on struct data
  - Can access and modify struct fields, return values, or perform operations

##### Struct Templates (Constructors)

  - All predetermined struct templates reside in the header file.
  - All structs always exist once defined until freed. Nullability of structs relies on a method belonging to all structs: IsNull(), which scans the types of all fields in the struct for nullability, then checks if all of the contents are null, and if so, returns a boolean true. Implicitly called when performing `obj == null`. Virtual, can be overridden.

  - Algorithm
    - Determine argument types. Explicit casts take priority, then input variable types, then numeric constant is checked directly.
    - Try overloads in declaration order; pick first that succeeds.
    - If multiple overloads accept the same parameter types -> compile error.
    - If none match -> compile error (narrowing requires explicit cast).

  - Allowed widenings
    - Unsigned: `byte->ushort->uint->ulong`
    - Signed: `sbyte->short->int->long`
    - Float: `float->double`
    - No sign-changes or narrowing implicitly.

### Examples

```cs
using namespace std;
// strings
string[64] str1 = "Hello, World!"; // 64 characters long
string str2 = "Hello, World!"; // 13 characters long, immutable, will create a new string when redefined
string str3; // invalid, compilation error

// arrays
int[8] a = { 1, 2, 3, 4 };
print(a.count); // returns 4
print(a.capacity); // returns 8

int[] a = { 1, 2, 3, 4 };
print(a.count()); // returns 4
print(a.capacity); // returns 4

// struct typedef
struct Image {
  string name;
  ushort x;
  ushort y;
}

// constructor
struct Image {
  Image(string name, byte x, byte y){ /*...*/ }
  Image(string name, ushort x, ushort y){ /*...*/ }
  string name;
  ushort x;
  ushort y;
}

// overloads
Image a = ("wendy.jpg", 200, 200);            // first overload if types fit
Image b = ("wendy.jpg", 500, 500);            // falls through to u16/u16
Image c = ("wendy.jpg", (ushort) 200, 200);   // explicit cast forces second
Image d = ("wendy.jpg", (ushort), (ushort));  // type casting allowed even with no input if properties are nullable

// overloads 2
struct Image {
  Image(string name, ushort x, ushort y){ /*...*/ }
  Image(string name, byte x, byte y){ /*...*/ }
  /*
  ...
  ...
  */
}

Image a = ("wendy.jpg", 200, 200);  // successfully fits into ushort (declared first), so it is declared as such.
Image b = ("wendy.jpg", 500, 500);  // also declares as ushort (correctly).

// manual declaration
struct a = {"wendy.jpg", 1000, 500}; // will default to int
```