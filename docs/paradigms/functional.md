# Functional Programming

Suede supports several functional programming features that complement its procedural foundation.

## Pattern Matching

Pattern matching is statically typed and provides compile-time exhaustiveness checking. Match on values and ranges with type safety.

## Ranges

The `..` operator creates inclusive ranges for iteration and array slicing.

## Spread Operators

Spread operators expand arrays inline for concatenation and composition.

## Expression-Bodied Methods

Methods with a single expression can use `=>` syntax for concise definitions.

## Example Usage

```c++
// pattern matching (statically typed)
string classify(uint value) => match value {
  0 => "zero",
  1..10 => "small",
  11..100 => "medium",
  _ => "large"
}

// ranges
for (i in 0..10) print(i);  // 0 through 10 inclusive

int[] numbers = { 1, 2, 3, 4, 5 };
int[] middle = numbers[1..3];  // { 2, 3, 4 }

// spread operators
int[] a = [ 1, 2, 3 ];
int[] b = [ 4, 5, 6 ];
int[] combined = [ ..a, ..b ];  // { 1, 2, 3, 4, 5, 6 }

// expression-bodied methods
int square(int x) => x ** 2;
```
