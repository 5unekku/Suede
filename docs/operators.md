# Operators

## Addition

```c++
int num = 5;
print(num + 2); // 7
print(num++); // increment after use (prints 5)
print(num); // 6
print(++num); // increment before use (prints 7)
num += 2; // adds 2 (9)
```

## Subtraction

```c++
int num = 5;
print(num - 2); // 3
print(num--); // decrement after use (prints 5)
print(num); // 4
print(--num); // decrement before use (prints 3)
num -= 2; // subtracts 2 (1)
```

## Multiplication

```c++
int num = 5;
print(num * 2); // 10
num *= 2; // multiplies by 2 (10)
```

## Division

```c++
int num = 5;
print(num / 2); // 2 (2.5, truncated since int)
num /= 2; // divides by 2 (1)
num = 15 % 10; // modulo, divide and retrieve remainder (5)
num %= 4; // 1
```

## Exponents

```c++
int num = 5;
print(num ** 2); // 25
num **= 2; // raises to the second power (25)
num ^*= 2; // lowers to the fourth root (5)
power(num, 2) // changes num in place (25) (void function)
int num2 = root(num, 2) // returns second root of num to num2 (5) (int function)
```

## Boolean Operators

```c++
bool state = true;
print(!state); // false (inverts value)
state~~; // false (inverts value in place)
~~state; // true (identical, but can be used to invert before accessing value)
```

## Bitwise Operators

```c++
int num1 = 0b00001111;
int num2 = 0b00110011;
print((num1 & num2).stringify("0b")); // bitwise and (0b00000011)
print((num1 | num2).stringify("0b")); // bitwise or (0b00111111)
print((num1 ^ num2).stringify("0b")); // bitwise xor (0b00111100)
print((~num1).stringify("0b")); // bitwise not (0b11110000) (inverts all bits)
num2 = num2 >> 2; // bit shift right (0b00001100)
num1 <<= 2; // bit shift left + assignment (0b00111100)
num1 ^= num2; // xor + assignment (0b00110000) (consistent with other operators)
```


## Special Operators

```c++
// minimum operator (assigns only if lower than current contents)
int min = 5;
min <?= 10; // 5
min <?= 6; // 5
min <?= 3; // 3

// maximum operator (assigns only if higher than current contents)
int max = 5;
max >?= 2; // 5
max >?= 4; // 5
max >?= 9; // 10
```