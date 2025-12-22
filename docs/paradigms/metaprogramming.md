# Metaprogramming

Suede provides compile-time metaprogramming features that enable code transformation and optimization without runtime overhead.

## The `let` Keyword

The `let` keyword acts as pure syntactic sugar for direct references. Let bindings are fully replaced by their contents during compilation, creating zero-cost aliases.

The primary use case is naming subexpressions to avoid repetition and improve readability without introducing runtime variables.

Characteristics:
- Compile-time only (no runtime representation)
- Direct textual substitution (not a variable or reference)
- Cannot be reassigned
- Each use is replaced with the original expression

Important: Let bindings are text replacements, not variables. If the bound expression has side effects, those effects occur at each substitution site. For single evaluation, use a regular variable instead.

## Example Usage

```c++
// avoiding repetition
int targetIndex = findIndex(entities, target); // not recommended to use let for methods since recomputation is required (let is purely for substitution)
let Entity targetEntity = entities[targetIndex]; // array access is zero-cost but more readable as a variable
targetEntity.health -= damage;
targetEntity.lastHit = time;
targetEntity.status = DAMAGED;

// intermediate calculations
let float dx = target.x - player.x;
let float dy = target.y - player.y;
let float distance = sqrt(dx ** 2 + dy ** 2);
applyForce({ dx / distance, dy / distance });

// critical difference: let vs variables
let int id = getNextId();
int a = id;  // calls getNextId()
int b = id;  // calls getNextId() again (twice total!)

int stored = getNextId();  // calls once, stores result
int c = stored;  // reads from stored
int d = stored;  // reads from stored
```
