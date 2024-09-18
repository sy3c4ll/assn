#let title = [CSED211: Data Lab2 Report]

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
  2024-09-12/2024-09-18 \
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

= Problem Statement

This lab presents a second set of puzzles, two of which are related to integer
arithmetic and the other four to floating-point arithmetic. The two categories
each have separate rulesets, allowing different sets of operations and
constructs.

== Integer Arithmetic

+ `negate(x)`: Return `-x` for two's complement integer `x`
+ `isLess(x, y)`: Return `1` if `x < y` and `0` otherwise

As with the previous lab, the assignment permits only straightline code with
8-bit signed constants and the following 8 operators only:

- `!`: boolean NOT
- `~`: bitwise NOT
- `&`: bitwise AND
- `^`: bitwise XOR
- `|`: bitwise OR
- `+`: addition
- `<<`: left shift
- `>>`: right shift

== Floating-Point Arithmetic

+ `float_abs(uf)`: Return the absolute value of a floating-point number
+ `float_twice(uf)`: Return the floating-point number doubled
+ `float_i2f(x)`: Return the floating-point representation of an integer
+ `float_f2i(uf)`: Return the integer representation of a floating-point number

Now all integer and unsigned operations and constants are allowed, as well as
standard control structures such as loops and conditionals. However, the use of
any data type other than `int` and `unsigned` is disallowed. Specifically,
floating-point builtin data types, operations and constants are strictly
prohibited.

= Implementation

== `negate(x)`

One of the properties of two's complements is that their values are one larger
than one's complements. Since the two's and one's complement for `x` is `-x` and
`~x` respectively, the following equality holds:

`-x == ~x + 1`

```c
int negate(int x) {
  return ~x + 1;
}
```

== `isLess(x, n)`

`x < y` holds when `x - y < 0`, which can be discerned by `x - y`'s sign.
However, the possibility of a subtraction overflow must also be considered.

`x - y` is equal to `x + (-y)`, and with the same principles as `negate(x)`,
`-y` can be calculated as `~y + 1`. Therefore, `x - y` can be calculated as
`x + ~y + 1`.

Overflow cannot occur when `x` and `y` have the same sign, as the larger
absolute value will only be decreased by the subtraction. The rest can be split into two cases, where:

1. `x` is non-negative and `y` is negative
  `x >= 0 > y` therefore `x < y` is always false.

2. `x` is negative and `y` is non-negative
  `x < 0 <= y` therefore `x < y` is always true.

Since the sign of an integer is its top bit, the sign of, say, `x` can be
differentiated by `x >> 31`, evaluating to `-1` if `x` is negative and `0`
otherwise. We define `sx` and `sy` as such values for `x` and `y` respectively.

All of the above can be aggregated into the claim that `x < y` if and only if:

*_Either `x` is negative and `y` is non-negative; or `x` and `y` have the same sign and
`x - y == x + ~y + 1` is negative._*

Taking care to make sure the `-1`s are masked into `1`s for the return value:

```c
int isLess(int x, int y) {
  int sx = x >> 31, sy = y >> 31;
  return sx & !sy | !(sx ^ sy) & x + ~y + 1 >> 31;
}
```

== `float_abs(uf)`

While the sign of a floating-point number is determined by its top bit, much
like two's complement integers, the method of expressing a negative number
differs to that of integers in that two floating-point numbers with the same
absolute value but different signs have the same representation in all but the
sign bit. Therefore, the sign bit can be toggled to obtain the absolute value of
a floating-point number. But now here's the catch.

Normally the sign bits of NaNs are 'most often ignored' (per Wikipedia), but
`btest` strictly checks for an equal bit pattern between the argument and the
return value. Therefore, the sign bit of a NaN must be preserved, with a
separate condition.

To discern NaNs from numbers and infinities, the exponent bits must be all `1`s
and the fraction bits must be non-zero. The sign bit can be toggled for all
other cases.

All of the above can be implemented with:

```c
unsigned float_abs(unsigned uf) {
  unsigned exp = uf >> 23 & 0xff;
  unsigned frac = uf & 0x7fffff;
  return exp == 0xff && frac ? uf : uf & 0x7fffffff;
}
```

== `float_twice(uf)`

Operation behaviour can be split into three cases, by the argument `float`:

+ NaNs and infinities: Return the argument unchanged
  By the problem statement, the return value must be exactly equal to the
  argument.
+ Denormalised numbers: Left-shift the fraction bits by 1
  Denormalised numbers are those with an exponent of `0`, and the fraction bits
  are the 23 bits following the exponent bits. Left-shifting the fraction bits
  by 1 is equivalent to doubling the number, and in the case of an overflow, the
  exponent will be incremented by 1, normalising the number while preserving the
  value. All the above can be implemented by left-shifting the argument by 1 and
  ORing the sign bit back in.
+ Normalised numbers: Increment the exponent by 1
  Normalised numbers are those with an exponent between `0x01` and `0xfe`. The
  exponent can be incremented by 1 by adding `0x800000` to the argument. In the
  case of an overflow, the exponent will be incremented by 1, becoming an
  infinity or a NaN. Since behaviour for such a case was defined neither by the
  problem statement nor IEEE754, the implementation will leave this part as
  undefined behaviour, and this will be presumed to be correct.

The cases can be discerned by the exponent bits, which are the 8 bits following
the sign bit. The exponent bits are all `1`s for NaNs and infinities, and all
`0`s for denormalised numbers. Therefore, the following implementation can be
used:

```c
unsigned float_twice(unsigned uf) {
  unsigned exp = uf >> 23 & 0xff;
  if (exp == 0xff) {
    return uf;
  } else if (exp == 0) {
    return uf << 1 | uf & 0x80000000;
  } else {
    return uf + 0x800000;
  }
}
```

== `float_i2f(x)`

First, `0` is unique out of all integer values in that expressed as a floating-
point number, it is denormalised as opposed to all other values which become
normalised in their floating-point representations. As such, we filter out `0`s
in a conditional and return its floating-point representation (which also
happens to be `0x00000000`) early.

The representation of negative numbers in two's complement integers and IEEE754
floating-point numbers are very different, therefore we will separate the sign
early and deal with the argument's absolute value only from now on. The sign of
integer `x` can be discerned with bitwise AND `&`-ing the mask `0x80000000`, to
leave only the top bit. For negative integers this value will be `0x80000000`,
while for non-negative integers it will be `0`. A ternary operation will coerce
this value into `true` and `false` respectively, allowing us to assign a new
variable `-x` and `x` in their respective cases which is its absolute value.

Then, the exponent must be calculated. The exponent is the number of bits
required to represent the absolute value of the integer, minus one. This can be
calculated by right-shifting the absolute value by 1 until it becomes `0`, and
counting the number of shifts. The exponent is biased by `0x7f`, and the
exponent bits are the 8 bits following the sign bit. The exponent can be
calculated by adding `0x7f` to the number of shifts, and left-shifting the
result by 23 bits.

The fraction bits are the remaining bits following the exponent bits. The
mantissa can be aligned left by left-shifting the absolute value by `31 - expn`
bits, dropping the top bit with one more left-shift, then right-shifting the
result by 9 bits. The left-shifts are not done in one step to prevent overflow.

The fraction bits must be rounded to the nearest even number. The guard bit is
defined as the last bit of the fraction bits, the round bit is the bit following
the guard bit, and the sticky bit is the bitwise OR `|` of all bits following
the round bit. Rounding must happen when either the round bit is `1` and the
guard bit is `1`, or the guard bit is `1`, round bit is `1` and the sticky bit
is `0`. The fraction bits can be incremented by `1` in such cases. A simple hack is used for post-normalisation, where the carry passes on to the exponent.

The sign, exponent, and fraction bits can be combined to form the floating-point
representation of the integer. The floating-point representation is the sign
bit, exponent bits, and fraction bits concatenated together.

The above can be implemented as follows:

```c
unsigned float_i2f(int x) {
  unsigned sign_part = x & 0x80000000;
  unsigned exp_part;
  unsigned frac_part;
  unsigned expn, xc;
  if (!x)
    return 0;
  if (sign_part)
    x = -x;
  for (expn = -1, xc = x; xc; ++expn, xc >>= 1);
  exp_part = (expn + 0x7f) << 23;
  frac_part = x << 31 - expn << 1 >> 9;
  if (expn > 23
    && x >> expn - 24 & 1
    && (x >> expn - 23 & 1
      || x & (1 << expn - 24) - 1))
    ++frac_part;
  return sign_part + exp_part + frac_part;
}
```

== `float_f2i(uf)`

Let us start with computing the sign, exponent, and mantissa of the floating-
point number. The sign is the top bit of the argument, the exponent is the 8
bits following the sign bit, and the mantissa is the 23 bits following the
exponent bits. The exponent is biased by `0x7f`, and the mantissa is normalised
by adding `0x800000` to it. The exponent can be used to determine the behaviour
of the function:

+ If the exponent is greater than or equal to `32`, the number is too large to
  be represented as an integer, and the function should return `0x80000000`. NaNs
  and infinities are coincidentally included in this case as well.
+ If the exponent is less than `0`, the number is too small to be represented as
  an integer, and the function should return `0`. `0` itself is coincidentally
  included in this case as well.
+ Otherwise, the number can be represented as an integer. The mantissa should be
  shifted left by `expn - 23` if `expn` is greater than `23`, and right by
  `23 - expn` otherwise, to align the mantissa bits to their proper place. The sign
  should be set with two's complement if the sign bit of the argument is `1`.

The above can be implemented as follows:

```c
int float_f2i(unsigned uf) {
  int sign = uf >> 31;
  int expn = (uf >> 23 & 0xff) - 0x7f;
  int mantissa = uf & 0x7fffff | 0x800000;
  if (expn >= 32) {
    return 0x80000000;
  } else if (expn < 0) {
    return 0;
  } else {
    return (expn > 23 ? mantissa << expn - 23 : mantissa >> 23 - expn) * (sign ? -1 : 1);
  }
}
```

= Conclusion

#figure(
  image("result.png"),
  caption: [Output from `driver.pl`],
)

= References

- #link("https://en.wikipedia.org/wiki/NaN")[NaN - Wikipedia]
- #link("https://en.wikipedia.org/wiki/IEEE_754")[IEEE 754 - Wikipedia]
- #link("https://en.cppreference.com/w/c/language/operator_precedence")[C Operator Precedence - cppreference.com]