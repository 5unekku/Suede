# Suede

Suede is a language designed as a successor C, C++ and Rust, focused on zero-cost abstractions, quality-of-life improvements, and pretty, easy to read syntax, while maintaining the core of C.

It preserves low-level control while reducing boilerplate and introducing modern language features.

Suede intends to maintain C’s capacity for low-level programming, C++'s capacity for streamlined development via efficient abstractions and modernized syntax, and Rust's compile time safe memory management.

# Specifications
   
## Types

### 1. Default Types

  - C-like types (`(u)int`/`float`/`bool` etc. + derivatives)

  - Possess minimal properties like `size` (object-oriented alternative to `sizeof(type)`), which are compile time constants and cannot be modified
   
  - Non-nullable by default, can be forced nullable via `type?` (sentinel value; n amount of checks where n = bits in type). Will default to 0 if not defined.


### 2. Arrays

  - Immutable, contents mutable.

   #### Properties
  - `size` (memory usage in bytes)
   
  - `capacity` (total indices)
   
  - `stride` (size of the type of the array (returns type.size); space between the beginnings of indices)

   #### Methods
  - `arr.count()` (shorthand for `std.array.count(arr)`, returns total non-`null` indices)

### 3. Strings

  - `string` is an immutable type that is non-nullable and requires assignment

  - `string<N>` is mutable, fixed-capacity.
   
  - Same properties and methods of Arrays. `std.string.count(str)` aliased to `std.array.count(str)`

### 4. Objects

  - `object Name { … }` are created manually inside of program or via templates, which use constructors to create objects depending on inputs. Templates are immutable, and objects constructed

  - `struct` functionality is wrapped into `object`s; `object`s can simply exclude methods for identical functionality

  - Instances have no runtime header beyond fields
  
  - Fields: Values of variables inside of objects (exclusive to objects)

#### Fields

  - Allowed

    - Constant values.

  - Disallowed

    - Anything non-constant, requiring more than value fetching. Such values must be calculated via methods.

#### Methods

  - Functions contained in objects that take no parameters

  - Uses object fields, modifying them and/or returning a value through calculations involving the fields

#### Object templates (Constructors)

  - All predetermined Object templates reside in the header file.
   
  - All objects always exist once defined until freed. Nullability of objects relies on a method belonging to all objects: IsNull(), which scans the types of all fields in the object for nullability, then checks if all of the contents are null, and if so, returns a boolean true. Implicitly called when performing `obj == null`. Virtual, can be overridden.

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


<!-- ## Memory Management, Ownership & Borrowing
TODO -->
  <!-- - Rules

    - Many immutable borrows or one mutable borrow at a time, not both.

    - Borrows cannot outlive owners.

    - Owners cannot move/destroy while borrows exist.

    - Reborrow immutably from a mutable borrow is allowed within its lifetime.

  - Forms

    - `&T` (immutable), `&mut T` (mutable); lifetimes inferred.

    - `str` is a borrowed view; `string<N>` is owned.

  - Effects

    - Prevents data races, use-after-free, and mutation during reads. -->

## Examples

```cs
using std
// strings
string<64> str1 = "Hello, World!"; // 64 characters long
string str2 = "Hello, World!"; // 13 characters long, immutable, will create a new string when redefined
string str3; // invalid, compilation error

// arrays
int[8] a = { 1, 2, 3, 4 };
print(a.count()); // returns 4
print(a.capacity); // returns 8

int[] a = { 1, 2, 3, 4 };
print(a.count()); // returns 4
print(a.capacity); // returns 4

// overloads
object image {
  (string name, byte x, byte y);
  (string name, ushort x, ushort y);
}

image a = ("wendy.jpg", 200, 200);            // first overload if types fit
image b = ("wendy.jpg", 500, 500);            // falls through to u16/u16
image c = ("wendy.jpg", (ushort) 200, 200);   // explicit cast forces second
image d = ("wendy.jpg", (ushort), (ushort));  // type casting allowed even with no input if properties are nullable

// overloads 2
object image (string name, ushort x, ushort y);
object image (string name, byte x, byte y);

image a = ("wendy.jpg", 200, 200);  // successfully fits into ushort (declared first), so it is declared as such.
image b = ("wendy.jpg", 500, 500);  // also declares as ushort (correctly).

// manual declaration
object a = {"wendy.jpg", 1000, 500};
```