# Functional Features

## Switch Expressions

```cs
// Switch as expression (returns value)
string result = value switch {
    0 => "zero",
    1 => "one",
    >= 2 and <= 10 => "small",
    _ => "large"
};

// Pattern matching with types
string message = obj switch {
    int i => "integer: " + i,
    string s => "string: " + s,
    _ => "unknown"
};

// Destructuring in switch
Point p = GetPoint();
string quadrant = p switch {
    { x: 0, y: 0 } => "origin",
    { x: > 0, y: > 0 } => "quadrant 1",
    { x: < 0, y: > 0 } => "quadrant 2",
    { x: < 0, y: < 0 } => "quadrant 3",
    { x: > 0, y: < 0 } => "quadrant 4",
    _ => "on axis"
};

// Traditional switch statement also supported
switch (value) {
    case 0:
        print("zero");
        break;
    case 1:
        print("one");
        break;
    default:
        print("other");
        break;
}
```

## Ranges and Spread Operator

### Range Expressions
```cs
// Range expressions for iteration
for (int i in 0..10) {  // 0 to 9 (exclusive end)
    print(i);
}

for (int i in 0..=10) {  // 0 to 10 (inclusive end)
    print(i);
}

// Ranges with custom step (potential)
for (int i in 0..100 step 5) {
    print(i);  // 0, 5, 10, 15, ...
}
```

### Spread Operator
```cs
// Spread in array literals
int[] arr1 = {1, 2, 3};
int[] arr2 = {4, 5, 6};
int[] combined = {..arr1, ..arr2};  // {1, 2, 3, 4, 5, 6}

// Mix with regular elements
int[] extended = {0, ..arr1, 10};  // {0, 1, 2, 3, 10}

// Spread in function calls
void sum(int a, int b, int c) => a + b + c;
int[] nums = {1, 2, 3};
int result = sum(..nums);

// Rest in destructuring
[first, second, ..rest] = {1, 2, 3, 4, 5};
// first = 1, second = 2, rest = {3, 4, 5}

[head, ..tail] = numbers;
// head = first element, tail = everything else

[..init, last] = numbers;
// init = all but last, last = last element
```

## Foreach Loop

Enhanced iteration with cleaner syntax than traditional for loops.

```cs
// Basic foreach
int[] numbers = {1, 2, 3, 4, 5};
foreach (int n in numbers) {
    print(n);
}

// With index
foreach (int n, int i in numbers) {
    print("Index {}: {}", i, n);
}

// Over ranges
foreach (int i in 0..10) {
    print(i);
}

// Over strings (character iteration)
string text = "hello";
foreach (char c in text) {
    print(c);
}

// Mutable iteration (if array allows)
int[] nums = {1, 2, 3};
foreach (mut int n in nums) {
    n *= 2;  // modifies array in place
}
```

## Array Methods

Functional-style collection operations that enable expressive data transformations.

### Map
Transform each element in a collection.

```cs
int[] nums = {1, 2, 3, 4, 5};

// Map - transform each element
int[] doubled = nums.map((x) => x * 2);
// Result: {2, 4, 6, 8, 10}

// Map with index
int[] indexed = nums.map((x, i) => x + i);
// Result: {1, 3, 5, 7, 9}

// Map to different type
string[] strings = nums.map((x) => "Number: " + x);
// Result: {"Number: 1", "Number: 2", ...}
```

### Filter
Keep only elements that match a condition.

```cs
// Filter - keep elements matching condition
int[] evens = nums.filter((x) => x % 2 == 0);
// Result: {2, 4}

int[] large = nums.filter((x) => x > 3);
// Result: {4, 5}

// Filter with complex logic
int[] filtered = nums.filter((x) => {
    bool is_prime = check_prime(x);
    bool is_large = x > 2;
    return is_prime && is_large;
});
```

### Reduce
Aggregate collection into a single value.

```cs
// Reduce - aggregate to single value
int sum = nums.reduce(0, (acc, x) => acc + x);
// Result: 15

// Product
int product = nums.reduce(1, (acc, x) => acc * x);
// Result: 120

// Find maximum
int max = nums.reduce(nums[0], (acc, x) => x > acc ? x : acc);

// Build string
string joined = strings.reduce("", (acc, s) => acc + s + " ");
```

### Method Chaining
Combine operations for powerful transformations.

```cs
// Chain operations
int result = nums
    .filter((x) => x > 2)      // {3, 4, 5}
    .map((x) => x * x)          // {9, 16, 25}
    .reduce(0, (acc, x) => acc + x);  // 50

// Complex pipeline
string[] names = {"Alice", "Bob", "Charlie", "David"};
string result = names
    .filter((name) => name.count > 3)
    .map((name) => name.to_upper())
    .reduce("", (acc, name) => acc + name + ", ");
// Result: "ALICE, CHARLIE, DAVID, "
```

### Other Useful Methods
```cs
// Any - check if any element matches
bool has_even = nums.any((x) => x % 2 == 0);  // true

// All - check if all elements match
bool all_positive = nums.all((x) => x > 0);  // true

// Find - get first matching element
int? first_large = nums.find((x) => x > 3);  // 4

// Take - get first n elements
int[] first_three = nums.take(3);  // {1, 2, 3}

// Skip - skip first n elements
int[] after_two = nums.skip(2);  // {3, 4, 5}

// Reverse
int[] reversed = nums.reverse();  // {5, 4, 3, 2, 1}

// Sort
int[] sorted = nums.sort();
int[] sorted_desc = nums.sort((a, b) => b - a);
```

## Lambda Expression Bodies

Concise function syntax for simple operations.

### Expression-Bodied Functions
```cs
// Single expression - no braces or return needed
int add(int a, int b) => a + b;

string greet(string name) => "Hello, " + name;

bool is_even(int x) => x % 2 == 0;

// With multiple statements, use braces
int complex(int x) => {
    int temp = x * 2;
    int result = temp + 10;
    return result;
};
```

### Struct Methods with Lambdas
```cs
struct Point {
    int x;
    int y;
    
    // Expression-bodied method
    int manhattan() => abs(x) + abs(y);
    
    // Return struct literal
    Point add(Point other) => Point {
        x: this.x + other.x,
        y: this.y + other.y
    };
    
    // With block
    Point scale(int factor) => {
        return Point {
            x: this.x * factor,
            y: this.y * factor
        };
    };
    
    // Boolean expression
    bool is_origin() => x == 0 && y == 0;
}
```

### Anonymous Functions
```cs
// For callbacks/map/filter - use parentheses for parameters
int[] doubled = nums.map((x) => x * 2);

// Multiple parameters
int[] results = data.map((x, idx) => x + idx);

// No parameters
void run(Function func) {
    func();
}
run(() => print("hello"));

// Multi-line anonymous function
int[] filtered = nums.filter((x) => {
    bool is_prime = check_prime(x);
    bool is_large = x > 10;
    return is_prime && is_large;
});

// Capturing variables
int threshold = 10;
int[] above_threshold = nums.filter((x) => x > threshold);
```

### Property Getters
```cs
struct Rectangle {
    int width;
    int height;
    
    // Computed property using lambda
    int area => width * height;
    int perimeter => 2 * (width + height);
    bool is_square => width == height;
}

// Usage
Rectangle r = {width: 5, height: 10};
print(r.area);  // 50 (computed on access)
```

## Additional Functional Features

### Immutability by Default
```cs
// Variables are immutable by default
int x = 5;
x = 10;  // Compile error

// Use mut keyword for mutability
mut int y = 5;
y = 10;  // OK

// Applies to function parameters too
void process(int value) {
    value = 100;  // Compile error
}

void process_mut(mut int value) {
    value = 100;  // OK
}
```

### Option Type (Nullable Handling)
```cs
// Option type for explicit null handling
Option<int> find_index(int[] arr, int target) {
    for (int i = 0; i < arr.count; i++) {
        if (arr[i] == target) return Some(i);
    }
    return None;
}

// Pattern match to unwrap
Option<int> result = find_index(nums, 5);
int index = result switch {
    Some(idx) => idx,
    None => -1
};

// Or use ? operator for propagation
int? find_value(int[] arr, int index) {
    if (index >= arr.count) return null;
    return arr[index];
}
```

### Destructuring
```cs
// Array destructuring
[first, second, third] = {1, 2, 3};

// With spread
[head, ..tail] = {1, 2, 3, 4, 5};

// Struct destructuring
Point { x, y } = get_point();

// With renaming
Point { x: px, y: py } = point;

// In function parameters
void process(Point { x, y }) {
    print("x: {}, y: {}", x, y);
}

// In foreach
Point[] points = {Point{1, 2}, Point{3, 4}};
foreach (Point {x, y} in points) {
    print("({}, {})", x, y);
}
```

### Pipe Operator (Potential)
```cs
// Chain operations left-to-right
string result = input
    |> trim()
    |> to_lower()
    |> replace("_", "-");

// Equivalent to nested calls
string result = replace(to_lower(trim(input)), "_", "-");

// With method chaining as alternative
string result = input.trim().to_lower().replace("_", "-");
```

## Design Principles

These functional features follow Suede's core principles:

1. **Zero-cost abstractions** - Map/filter/reduce compile to efficient loops, no runtime overhead
2. **Explicit over implicit** - Mutability is explicit with `mut`, nullability with `?`
3. **Clean syntax** - C#-influenced style that's familiar and readable
4. **Procedural foundation** - Functional features enhance, don't replace procedural style
5. **No hidden complexity** - No garbage collection, no lazy evaluation surprises
6. **Composability** - Features work together naturally (foreach + ranges, switch + destructuring)

These features make code more expressive and safe while maintaining the performance and control expected from a systems programming language.
