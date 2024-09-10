#let title = [CSED211: Data Lab1 Report]

#set page(
  paper: "a4",
  header: align(right + horizon, title),
  numbering: "- 1 / 1 -",
)
#set par(justify: true)
#set text(
  font: "IBM Plex Serif",
  size: 11pt,
  hyphenate: false,
)
#set heading(numbering: "I a. ")
#show raw: set text(font: "IBM Plex Mono")

#align(center, text(size: 24pt, weight: "bold",
  title
))
#align(right, text(style: "italic")[
  2024-09-04/2024-09-11 \
  20230262 / Yeonung Kim \
  yeonung04\@postech.ac.kr \
])
#rect(width: 100%, align(center)[
  #block(text(size: 13pt, weight: "bold")[
    명예서약 Honour Code
  ])
  나는 이 프로그래밍 과제를 다른 소스를 인용없이 참고하거나, \
  다른 사람의 부적절한 도움을 받지 않고 완수하였습니다. \
  I hereby pledge on my honour that I have not given or received \
  any unauthorised assistance on this assignment. \
])

// #show: rest => columns(2, rest)

= Problem Statement

The lab presents five puzzles of implementing:

+ `int bitNor(int x, int y)`: bitwise NOR (NOT OR) of `x` and `y`
+ `int isZero(int x)`: equality of `x` to 0
+ `int addOK(int x, int y)`: overflow check for addition of `x` and `y`
+ `int absVal(int x)`: absolute value of `x`
+ `int logicalShift(int x, int n)`: logical right shift of `x` to `n`

However, all problems have extra constraints, restricting the use of operators to select allowed bitwise operations & co., as well as the total number of such operations. Furthermore, all uses of conditional and loop constructs are prohibited. The following operators are generally allowed:

+ `!`: boolean NOT
+ `~`: bitwise NOT
+ `&`: bitwise AND
+ `^`: bitwise XOR
+ `|`: bitwise OR
+ `+`: addition
+ `<<`: bitwise left shift
+ `>>`: bitwise right shift

While some specifics on the problem constraints have been omitted for brevity, the main gist is that five operations require implementing with only a few fundamental bitwise manipulations available.

= Implementation

== `int bitNor(int x, int y)`: bitwise nor (not or) of `x` and `y`

Reference implementation:

```c
int bitNor(int x, int y) {
  return ~(x | y);
}
```

This problem allows at most 8 operations, and further limits the allowed operators to bitwise NOT `~` and bitwise AND `&`.

#line()

By De Morgan's laws, `~(x | y) == ~x & ~y`. Therefore, the function can be trivially implemented as

```c
int bitNor(int x, int y) {
  return ~x & ~y;
}
```

Solved in 3 operations.

== `int isZero(int x)`: equality of `x` to 0

Reference implementation:

```c
int isZero(int x) {
  return x == 0;
}
```

This problem allows at most 2 operations.

#line()

Before performing its function boolean NOT `!` coerces an integer operand into a boolean, which value is determined solely by whether the integer is zero or non-zero, being converted into 0 and 1 respectively. Therefore, a boolean coercion followed by an inversion is the desired output, this can be performed with a single boolean NOT `!`.

```c
int isZero(int x) {
  return !x;
}
```

Solved in 1 operation.

== `int addOK(int x, int y)`: overflow check for addition of `x` and `y`

Reference implementation:

```c
int addOK(int x, int y) {
  long long lsum = (long long) x + y;
  return lsum == (int) lsum;
}
```

This problem allows at most 20 operations.

#line()

One may note that an overflow in the addition of two integers with the same sign always appears to invert the sign in the result. This is not mere coincidence, but rather a consistent and explainable behaviour. For this proof, and the ensuing function implementation, all possible parameter values for `x` and `y` will be split into three cases:

+ `x` and `y` have different signs

  Addition between such values cannot overflow, since the bigger absolute value will only be shrunk on adding an absolutely smaller integer of the opposite sign.

+ `x` and `y` are both non-negative (with sign bit 0)

  The smallest overflown sum in such a case is obviously `0x80000000` = -2,147,483,648, which is one larger than `INT32_MAX` and is equal to `INT32_MIN`. The largest overflown sum is `0x7fffffff` + `0x7fffffff` = `0xfffffffe` = -2, and all values within this range are negative.

+ `x` and `y` are both negative (with sign bit 1)

  The largest overflown sum in such a case is obviously `0x7fffffff` = 2,147,483,647, which is one smaller than `INT32_MIN` and is equal to `INT32_MAX`. The smallest overflown sum is `0x80000000` + `0x80000000` = 0, and all values within this range are non-negative.

Therefore, either `x` and `y` have different signs, or their sum has a different sign from both `x` and `y`.

Signs can be retrieved with a right shift by 31. If `x`'s sign is 0 `x >> 31` is also 0, but if x's sign is 1 `x >> 31` may be either 1 or `0xffffffff` = -1, depending on whether a logical or arithmetic shift is performed. Since `31u` is a banned constant, we are locked to using arithmetic shifts.

Assigning `s1 = x >> 31` and `s2 = y >> 31`, we can check for their equality with `s1 ^ s2`. If they indicate the same sign the result will be 0, while if they are different -1 will be yielded.

Boolean operations can be mimicked with bitwise equivalents when both operands are 0 or 1. To ensure compatibility we must shrink {0, -1} from the previous operation into {0, 1}. This can be done in at least two ways: coercing the numbers into booleans with double boolean negation; or masking out everything but the lowest bit with `& 1`.

Combining every point, the following implementation is possible:

```c
int addOK(int x, int y) {
  int s1 = x >> 31, s2 = y >> 31, s3 = (x + y) >> 31;
  // return (s1 ^ s2) & 1 | !(s1 ^ s3) & !(s2 ^ s3);
  // Since s1 == s2 is guaranteed past the |, this can be further simplified to
  return (s1 ^ s2) & 1 | !(s1 ^ s3);
}
```

Solved in 9 operations.

== `int absVal(int x)`: absolute value of `x`

Reference implementation:

```c
int absVal(int x) {
  return (x < 0) ? -x : x;
}
```

This problem allows at most 10 operations.

#line()

Relying on the fact that a two's complement is a one's complement plus one, or otherwise observing that `x + ~x == 0xffffffff` and thus `x + ~x + 1 == 0`, we can draw that `-x == ~x + 1`. This will come in handy when we have to compute `-x`.

In order to differentiate by `x`'s sign, we must first retrieve it with `x >> 31`, which yields 0 when `x >= 0` and `0xffffffff` = -1 when `x < 0`. Here we note that the two possible values are very specific, in the sense that `x ^ 0x00000000 == x` and `x ^ 0xffffffff == ~x`.

This single XOR allows us to approach the answer rapidly, leaving `+ 1` for the negative case. This can also be done with the sign, with one's first instincts to subtract it to invert the sign, however being barred by the fact that neither subtraction nor negation is allowed. Otherwise `x >> 31u` allows one to perform a logical shift to retrieve 1 directly, but unsigned constants are similarly banned. Therefore we must spend an extra operand to coerce the sign into {0, 1}, such as:

```c
int absVal(int x) {
  return (x ^ x >> 31) + (x >> 31 & 1);
}
```

Solved in 5 operations.

== `int logicalShift(int x, int n)`: logical right shift of `x` to `n`

Reference implementation:

```c
int logicalShift(int x, int n) {
  unsigned u = (unsigned) x;
  unsigned shifted = u >> n;
  return (int) shifted;
}
```

This problem allows at most 20 operations.

#line()

Obviously `x >> n` does not yield the desired result. This is because in C, the behaviour of the right bitwise shift operator depends on the type of the operand; when the operands are signed integers, as in this question, the operator performs an arithmetic shift. Therefore, we must look for a way to circumvent or otherwise counteract the operator's behaviour.

One glaring way to do this is to zero out all the created bits, with a bitwise AND `&` and a mask to apply. The mask is a bit pattern `0b00...011...1`, with `n` 0s and `32 - n` 1s. How can this pattern be expressed within the constraints of allowed operators and constants?

One may observe expressing `0b00...011...1` as `~0b11...100...0` opens up new possibilities for creating the mask. For example, `0b11...100...0` (with `n` 1s and `32 - n` 0s) is equivalent to `0b100...0` (with 31 0s) arithmetic right shifted by `n - 1`, which is expressible by `(1 << 31) >> (n - 1) == 1 << 31 >> n << 1`. The mask is a bitwise NOT `~` of this value, and this needs only be applied to the arithmetic `x >> n` with a bitwise AND `&`, yielding the implementation:

```c
int logicalShift(int x, int n) {
  return x >> n & ~(1 << 31 >> n << 1);
}
```

Solved in 6 operations.

= Conclusion

#figure(
  image("result.png"),
  caption: [Output from `driver.pl`],
)

= References

- De Morgan's laws: https://en.wikipedia.org/wiki/De_Morgan%27s_laws
- Two's complement: https://en.wikipedia.org/wiki/Two%27s_complement
- Arithmetic shift: https://en.wikipedia.org/wiki/Arithmetic_shift
- C operators precedence: https://en.cppreference.com/w/c/language/operator_precedence