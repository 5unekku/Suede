# Structs

Structs are user-defined composite types that group related data and behavior. They can be manually created or constructed via struct templates (constructors).

Deliberately named `struct` (like in C) rather than `class` or `object` to emphasize procedural/functional programming over object-oriented paradigms.

## Structure

Structs can contain:
- Fields (data)
- Methods (functions)
- Properties (like C#)

Instances have no runtime header beyond fields, ensuring zero-cost abstraction.

## Fields

Fields store the state of a struct.

Allowed:
- Constant values

Disallowed:
- Anything non-constant requiring more than value fetching
- Such values must be calculated via methods

## Methods

Methods are functions associated with a struct type that can:
- Take parameters
- Access and modify struct fields
- Return values
- Perform operations

## Properties

Properties provide controlled access to fields through get and set accessors. They can have independent access modifiers for their get and set blocks.

Syntax:
- `get` - read accessor
- `set` - write accessor (implicit `value` parameter)

Properties can be:
- Read-only (get only)
- Write-only (set only)
- Read-write (both get and set)

Each accessor can have its own access modifier, allowing fine-grained control.

## Access Control

Access control is only available for struct members. Free functions and global variables have no access control.

Struct members can be marked as `public` or `private`. The default access level for all members is determined by the struct declaration:
- `struct` - members are public by default
- `public struct` - redundant, but valid
- `private struct` - members are private by default

Access modifiers apply to both fields and methods within the struct.

## Constructors

Constructors are defined as struct templates in the header file.

### Nullability

All structs always exist once defined until freed. Nullability relies on the `IsNull()` method:
- Belongs to all structs
- Scans the types of all fields for nullability
- Checks if all contents are null
- Returns boolean true if all nullable fields are null
- Implicitly called when performing `obj == null`
- Virtual, can be overridden

## Constructor Overloading

### Resolution Algorithm

1. Determine argument types
   - Explicit casts take priority
   - Then input variable types
   - Then numeric constant is checked directly

2. Try overloads in declaration order; pick first that succeeds

3. Error conditions:
   - If multiple overloads accept the same parameter types: compile error
   - If none match: compile error (narrowing requires explicit cast)

### Allowed Type Widenings

Unsigned: `byte -> ushort -> uint -> ulong`

Signed: `sbyte -> short -> int -> long`

Float: `float -> double`

No sign-changes or narrowing implicitly.

## Example Usage

```c++
// basic struct definition
struct Image {
  string name;
  ushort x;
  ushort y;
}

// struct with constructors
struct Photo {
  string name;
  ushort x;
  ushort y;

  Photo(string name, byte x, byte y) { /*...*/ }
  Photo(string name, ushort x, ushort y) { /*...*/ }
}

// constructor overload resolution
Photo a = ("wendy.jpg", 200, 200);            // first overload if types fit
Photo b = ("wendy.jpg", 500, 500);            // falls through to ushort/ushort
Photo c = ("wendy.jpg", (ushort) 200, 200);   // explicit cast forces second
Photo d = ("wendy.jpg", (ushort), (ushort));  // type casting allowed even with no input if properties are nullable

// declaration order matters
struct Document {
  string name;
  ushort x;
  ushort y;

  Document(string name, ushort x, ushort y) { /*...*/ }
  Document(string name, byte x, byte y) { /*...*/ }
}

Document doc1 = ("file.txt", 200, 200);  // successfully fits into ushort (declared first)
Document doc2 = ("file.txt", 500, 500);  // also declares as ushort (correctly)
Document doc2 = ("file.txt", (byte) 500, (byte) 500);  // casting forces it to be interpreted as byte, using second constructor

// manual struct initialization
Image manual = {"photo.jpg", 1000, 500};  // will default to int for numeric fields

// access control, public by default
struct Counter {
  int count;              // public by default
  private int _internal;  // explicitly private
}

// access control, private by default
private struct SecureData {
  string data;              // private by default
  public string id;         // explicitly public
}

// properties with get/set
struct Person {
  private string _name;
  private int _age;

  // read/write property
  string name {
    get => _name;
    set { /* validation */ }
  }

  // read only property (direct arrow)
  int age => _age;

  // roperty with access control on accessors (requires block)
  private int _id;
  int id {
    get => _id;
    private set => { /* validation */ };
  }

  // computed property (direct arrow)
  bool isAdult => _age >= 18;
}
```
