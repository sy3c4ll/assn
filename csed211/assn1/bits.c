/*
 *
 * CSED 211, Fall 2022
 * DataLAb: Manipulating Bits
 * Assigned: 2022-09-07
 * Due: 2022-09-18 23:59 pm
 *
 * Namgyu Park (namgyu.park@postech.ac.kr) is the lead person for this assignment.
 *
*/


#if 0
LAB L1 INSTRUCTIONS:
#endif

// General notes and observations.
// All unsigned ints seem to be represented by a normal signed int.
// Therefore, ints must be interpreted as bit patterns with signed arithmetic.
// Casting is not allowed, since it is also an operation.
// Evil pointer hacks are equally out of bounds, they also are casting.
// Discerning zero and non-zero bit patterns can be done with !,
// which shrinks the range into {0, 1}.
// Discerning negative and non-negative signed bit patterns is also trivial,
// with x >> sizeof(int) * 8 - 1.
// Signed bit patterns being 2's complements, this means x + -x = 0.
// 1's complements are ~x and 2's complements are 1's complements + 1.
// x + ~x = 0xffffffff, x + ~x + 1 = 0 = x + -x => -x = ~x + 1
// a - x = a + -x = a + ~x + 1

/*
 *   #Homework1-1 
 *   bitNor - ~(x|y) using only ~ and & 
 *   Example: bitNor(0x6, 0x5) = 0xFFFFFFF8
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */

int bitNor(int x, int y) {
  return ~x & ~y;
}


/*
 *   #Homework1-2
 *   isZero - returns 1 if x == 0, and 0 otherwise 
 *   Examples: isZero(5) = 0, isZero(0) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int isZero(int x) {
  return !x;
}


/* 
 *   #Homework1-3
 *   addOK - Determine if can compute x+y without overflow
 *   Example: addOK(0x80000000,0x80000000) = 0,
 *            addOK(0x80000000,0x70000000) = 1, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int addOK(int x, int y) {
  // As per tests.c, this is a signed integer addition
  // Addition overflow seems to change signs
  // With + and +, min overflow sum is 0x80000000 = -2147483648
  // and max is 0x7fffffff + 0x7fffffff = 0xfffffffe = -2
  // With - and -, max overflow sum is 0x7fffffff = 2147483647
  // and min is 0x80000000 + 0x80000000 = 0
  // With + and -, overflow cannot happen
  // Problem statement <=> x and y have different signs,
  // or they both have the same sign to the sum
  // Signs: s1 = x >> 31u (= 0, 1), s2 = y >> 31u, s3 = x + y >> 31u
  // Same: !(s1 ^ s2), different: s1 ^ s2
  // s1 ^ s2 | !(s1 ^ s3) & !(s2 ^ s3)
  // Since I can't use unsigned constants, I have to get creative with ! and &1
  int s1 = x >> 31, s2 = y >> 31, s3 = (x + y) >> 31;
  return ((s1 ^ s2) & 1) | !(s1 ^ s3);
  // Extra parens to satisfy dlc and gcc
}


/*   
 *   #Homework1-4
 *   absVal - absolute value of x
 *   Example: absVal(-1) = 1.
 *   You may assume -TMax <= x <= TMax
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4
 */
int absVal(int x) {
  // -x = ~x + 1
  // x >> 31 = 0 if x >= 0, 0xffffffff = -1 if x < 0 (arithmetic shift on signed int)
  // x >> 31u = 0 if x >= 0, 1 if x < 0 (logical shift on unsigned int)
  // (x ^ 0x00000000) = x, (x ^ 0xffffffff) = ~x
  // x >= 0 ? x : -x = (x ^ x >> 31) + (x >> 31u)
  return (x ^ x >> 31) + (x >> 31 & 1);
}


/*   
 *   #Homework1-5
 *   logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
  // x >> n obviously doesn't work - why?
  // x >> n performs an arithmetic shift and may fill 1s
  // Therefore I null all those fills - I can use &
  // The mask is 00...011...1 with n 0s and 32 - n 1s
  // How can this be expressed?
  // (1 << 33 - n) - 1... but I can't use -
  // 11...1 (with 32 1s) logical shr n... leads to a chicken and egg problem...
  // unless the mask can be made an unsigned integer... with ~0u >> n!
  // Nevermind, that's an illegal constant. (_whyyyyyyyyyy_)
  // ~11...100...0 (with n 1s and 32 - n 0s) which is 11...1 (with 32 1s) << 32 - n
  // or it's 100...0 (1 << 31) arithmetic shr n - 1
  return x >> n & ~(1 << 31 >> n << 1);
}

