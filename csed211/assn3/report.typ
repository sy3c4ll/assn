#let title = [CSED211: Bomb Lab Report]

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
  2024-09-26/2024-10-09 \
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

= Overview

This is the Bomb Lab.

As such, I will be breaking from my usual format.

This writeup is comprised of two sections:

+ Carefully defusing the Bomb
+ Brutally mutilating and dismembering the Bomb for fun and profit

= Carefully defusing the Bomb

The Bomb seemingly has 6 stages, each of which requires a password to defuse. However, on closer inspection of `phase_defused`, it is revealed that the Bomb has an extra 'secret phase'.

I've used IDA Pro by Hex-Rays to speed up my analysis. I gather this isn't exactly against the rules.

== Phase 1

This phase is trivial.

Decompiling reveals the following code:

```c
result = strings_not_equal(a1, "Wow! Brazil is big.");
if ( (_DWORD)result )
  explode_bomb();
```

Thanks for keeping the symbol names.

#text(size: 16pt, weight: "bold")[
  `Wow! Brazil is big.`
]

== Phase 2

I'll be going through the decompiled code part by part.

```c
read_six_numbers(a1, v3);
if ( *(_QWORD)v3 != 0x100000000LL )
  explode_bomb();
```

a1 is the input string, and v3 is an array of 6 integers. After filling in v3, the code checks if the QWORD at v3 is 0x100000000.

v3 is an array of DWORDs. v3[0] is 0, v3[1] is 1.

```c
v2 = (char *)&v3[2];
do
{
  result = (unsigned int)(*((_DWORD *)v2 - 1) + *((_DWORD *)v2 - 2));
  if ( *(_DWORD *)v2 != (_DWORD)result )
    explode_bomb();
  v2 += 4;
}
while ( v2 != &v4 );
```

v2 is obviously a counter, and it starts at v3[2]. The code then checks if the next DWORD is the sum of the previous two DWORDs. We know what this sequence is.

#text(size: 16pt, weight: "bold")[
  `1 1 2 3 5 8`
]

== Phase 3

```c
if ( (int)__isoc99_sscanf(a1, "%d %c %d", &v4, &v2, &v3) <= 2 )
  explode_bomb();
```

Input goes int, char, int. No, we don't need the spaces.

```c
switch ( v4 )
{
  case 0:
    result = 102LL;
    if ( v3 != 544 )
      explode_bomb();
    return result;
  case 1:
    result = 109LL;
    if ( v3 != 202 )
      explode_bomb();
    return result;
  case 2:
    result = 111LL;
    if ( v3 != 168 )
      explode_bomb();
    return result;
  case 3:
    result = 101LL;
    if ( v3 != 487 )
      explode_bomb();
    return result;
  case 4:
    result = 101LL;
    if ( v3 != 819 )
      explode_bomb();
    return result;
  case 5:
    result = 116LL;
    if ( v3 != 623 )
      explode_bomb();
    return result;
  case 6:
    result = 110LL;
    if ( v3 != 416 )
      explode_bomb();
    return result;
  case 7:
    result = 104LL;
    if ( v3 != 565 )
      explode_bomb();
    return result;
  default:
    explode_bomb();
}
if ( (_BYTE)result != v2 )
  explode_bomb();
```

If you thought the `return result`s in the switch cases were weird, you're right. The disassembly reveals the returns are actually just for exiting the switch; in other words, they're breaks.

Each of these cases are possible answers, we just have to convert `result` with ASCII.

#text(size: 16pt, weight: "bold")[
  - `0f544`
  - `1m202`
  - `2o168`
  - `3e487`
  - `4e819`
  - `5t623`
  - `6n416`
  - `7h565`
]

== Phase 4

```c
if ( (unsigned int)__isoc99_sscanf(a1, "%d %d", &v3, &v2) != 2 || v3 > 0xE )
  explode_bomb();
result = func4(v3, 0LL, 14LL);
if ( (_DWORD)result != 13 || v2 != 13 )
  explode_bomb();
```

Input is two ints, but the first must be at most 14 and the second must be 13. Now to `func4`.

```c
__int64 __fastcall func4(__int64 a1, __int64 a2, __int64 a3)
{
  int v3; // ebx
  __int64 result; // rax

  v3 = ((int)a3 - (int)a2) / 2 + a2;
  if ( v3 > (int)a1 )
    return v3 + (unsigned int)func4(a1, a2, (unsigned int)(v3 - 1));
  result = (unsigned int)v3;
  if ( v3 < (int)a1 )
    return v3 + (unsigned int)func4(a1, (unsigned int)(v3 + 1), a3);
  return result;
}
```

So a1 is compared to the midpoint of a2 and a3. If a1 is greater, the function is called with a2 and the midpoint - 1. If a1 is less, the function is called with the midpoint + 1 and a3. Each time the midpoint is added, and a1 is always kept.

Then, with what sum could `func4(v3, 0, 14)` yield 13?

```
 0 14 ->  7
 0  6 ->  3
 0  2 ->  1
 2  2 ->  2
```

7 + 3 + 1 + 2 = 13.

#text(size: 16pt, weight: "bold")[
  `2 13`
]

== Phase 5

```c
if ( (unsigned int)string_length() != 6 )
  explode_bomb();
for ( i = 0LL; i != 6; ++i )
  v3[i] = array_3162[a1[i] & 0xF];
v3[6] = 0;
result = strings_not_equal(v3, "bruins");
if ( (_DWORD)result )
  explode_bomb();
```

Oh, it's a substitution cipher. So what does 0x3162 look like?

```c
// This was transcribed myself from the hex at .rodata
char array_3162[16] = {'m', 'a', 'd', 'u', 'i', 'e', 'r', 's', 'n', 'f', 'o', 't', 'v', 'b', 'y', 'l'};
```

So,

+ `a1[0] & 0xF == 13`
+ `a1[1] & 0xF == 6`
+ `a1[2] & 0xF == 3`
+ `a1[3] & 0xF == 4`
+ `a1[4] & 0xF == 8`
+ `a1[5] & 0xF == 7`

There are many answers satisfying this condition. Here's a neat one:

#text(size: 16pt, weight: "bold")[
  `M&STX7`
]

(That's l33t for MASTER)

== Phase 6

```c
read_six_numbers(input, nums);
```

Yes, I actually had to name the variables for this one. Anyways, this is another six numbers problem.

```c
while ( 1 )                                   // Validate nums
{
  if ( (unsigned int)(*cur - 1) > 5 )
    explode_bomb();
  if ( ++ctr == 6 )
    break;
  icur = ctr;
  do
  {
    if ( *cur == nums[icur] )
      explode_bomb();
    ++icur;
  }
  while ( icur <= 5 );
  ++cur;
}                                             // END Validate nums
```

All numbers must be in `1..=6`, and no number can be repeated.

```c
for ( i = 0LL; i != 6; ++i )                  // Populate node_ptr_for_nums
{
  elem = nums[i];
  if ( elem <= 1 )
  {
    ptr = (int *)&node1;
  }
  else
  {
    elem_ctr = 1;
    ptr = (int *)&node1;
    do
    {
      ptr = (int *)*((_QWORD *)ptr + 1);      // Valiant anti-decompiler efforts, but this entire else block just means &node{elem}
      ++elem_ctr;
    }
    while ( elem_ctr != elem );
  }
  node_ptr_for_nums[i] = ptr;
}                                             // END Populate node_ptr_for_nums
```

Now here's an interesting one. This seemed to befuddle my decompiler, and it tried to do a lot of weird pointer casting. Looking at .data, I could understand why.

The nodes are each a 16-byte long data block, with the bottom 8 bytes initially holding a pointer to the next node. The top 8 bytes are the value of the node, though I doubt anything more than a DWORD is used. In other words, this is a linked list.

Here, the code is compiling a list of said node pointers in order of `node{nums[i]}`.

```c
node_ptr_cur2 = node_ptr_for_nums[0];         // Relink node{i} wrt nums[i]
node_ptr_it = &node_ptr_for_nums[1];
for ( node_ptr_cur = node_ptr_for_nums[0]; ; node_ptr_cur = node_ptr_cur_next )
{
  node_ptr_cur_next = *node_ptr_it;
  *((_QWORD *)node_ptr_cur + 1) = *node_ptr_it++;
  if ( node_ptr_it == (int **)nums )          // &node_ptr_for_nums[0] + 6 == &nums[0]
    break;
}
*((_QWORD *)node_ptr_cur_next + 1) = 0LL;     // END Relink node{i} wrt nums[i]
```

This is just relinking the nodes in the order of `node{nums[i]}`.

```c
down_ctr = 5;                                 // Pass condition
do
{
  result = **((unsigned int **)node_ptr_cur2 + 1);
  if ( *node_ptr_cur2 < (int)result )         // *node_ptr_for_nums[i] < *node_ptr_for_nums[i + 1]
    explode_bomb();
  node_ptr_cur2 = (int *)*((_QWORD *)node_ptr_cur2 + 1);
  --down_ctr;
}
while ( down_ctr );                           // END Pass condition
```

Then the code checks if the values of the nodes are in descending order with respect to `nums[i]`. This is the pass condition.

Now we can solve this.

+ `node1.data == 0x113`
+ `node2.data == 0x1EF`
+ `node3.data == 0x3D5`
+ `node4.data == 0x257`
+ `node5.data == 0x150`
+ `node6.data == 0x3DD`

#text(size: 16pt, weight: "bold")[
  `6 3 4 2 5 1`
]

== Secret phase

At `phase_defused`, we see the following:

```c
if ( num_input_strings == 6 )
{
  if ( (unsigned int)__isoc99_sscanf(&unk_6048B0, "%d %d %s", &v2, &v1, v3) == 3
    && !(unsigned int)strings_not_equal(v3, "SecretPhase") )
  {
    puts("Curses, you've found the secret phase!");
    puts("But finding it and solving it are quite different...");
    secret_phase();
  }
  puts("Congratulations! You've defused the bomb!");
  return puts("Your instructor has been notified and will verify your solution.");
}
```

So we need to deposit 'SecretPhase' at a random location (0x6048B0) in memory that even the compiler can't figure the type out.

Then we see this in `read_line`:

```c
v0 = num_input_strings;
v1 = (const char *)(80LL * num_input_strings + 0x6047C0);
v2 = strlen(v1) + 1;
if ( (int)v2 - 1 > 78 )
{
  puts("Error: Input line too long");
  v3 = num_input_strings++;
  v4 = 10LL * v3;
  input_strings[v4] = 0x636E7572742A2A2ALL;
  qword_6047C8[v4] = 0x2A2A2A64657461LL;
  explode_bomb();
}
```

The inputs are stored in the bss section at 0x6047C0, and are each at most 80 == 0x50 bytes long. After six phases, `phase_defused` `sscanf`s address 0x6048B0, which exactly coincides with phase 4's inputs. Coincidentally, phase 4 takes two integers, while the secret phase expects two integers followed by the string phrase SecretPhase.

Within `secret_phase`, we see the following:

```c
line = read_line();
v1 = strtol(line, 0LL, 10);
if ( (unsigned int)(v1 - 1) > 0x3E8 )         // v1 <= 0x3E9 == 1001
  explode_bomb();
if ( fun7(&n1, v1) != 6 )                     // n1 == 0x24 == 36
  explode_bomb();
puts("Wow! You've defused the secret stage!");
```

An extra integer is taken that is no larger than 1001, and `fun7` is called with `v1` and `&n1`.

First, what's `n1`?

```
0x0000000000000024 0x0000000000604130 0x0000000000604150 0x0000000000000000
```

The second and third QWORDs seem to be pointers. Looking at their addresses, we find respectively n21 and n22.

This seems similar to the linked list in phase 6, except we have two (or even three) pointers per node. We have a name for that; it's a tree.

I've transcribed the hex for `n`s to readable C code:

```c
struct node {
  int val;
  struct node* ptr[3];
} n1, n21, n22, n31, n32, n33, n34, n41, n42, n43, n44, n45, n46, n47, n48;

n1 = {0x24, {&n21, &n22}};
n21 = {0x08, {&n31, &n32}};
n22 = {0x32, {&n33, &n34}};
n31 = {0x06, {&n41, &n42}};
n32 = {0x16, {&n43, &n44}};
n33 = {0x2D, {&n45, &n46}};
n34 = {0x68, {&n47, &n48}};
n41 = {0x01};
n42 = {0x07};
n43 = {0x14};
n44 = {0x23};
n45 = {0x28};
n46 = {0x2F};
n47 = {0x63};
n48 = {0xE9};
```

This helps us see that the structure is that of a perfect binary tree, where in $n_{i j}$, $i$ is the depth and $j$ is the horizontal position.

```
n1 - n21 - n31 - n41
   |     |     |
   |     |     \ n42
   |     |
   |     \ n32 - n43
   |           |
   |           \ n44
   |
   \ n22 - n33 - n45
         |     |
         |     \ n46
         |
         \ n34 - n47
               |
               \ n48
```

Let's have a look inside `fun7`. While taking notes it seems I've rectified and cleaned up the decompiled code a bit, therefore I'll be using my own version.

```c
int fun7(struct node* n, int v) {
  if (n == NULL)
    return -1;

  if (n->val > v)
    return 2 * fun7(n->ptr[0], v);
  else if (n->val < v)
    return 2 * fun7(n->ptr[1], v) + 1;
  else
    return 0;
}
```

Like in phase 4, what order of calling `fun7` would yield 6?

+ `6 == 2 * 3`
+ `3 == 2 * 1 + 1`
+ `1 == 2 * 0 + 1`

For this,

+ ` n1.val == 0x24 > v && fun7(&n21, v) == 3`
+ `n21.val == 0x08 < v && fun7(&n32, v) == 1`
+ `n32.val == 0x16 < v && fun7(&n44, v) == 0`
+ `n44.val == 0x23 == v`

0x23 = 35.

#text(size: 16pt, weight: "bold")[
  `35`
]

== `answers.txt`

```
Wow! Brazil is big.
1 1 2 3 5 8
0f544
2 13 SecretPhase
M&STX7
6 3 4 2 5 1
35
```

= Brutally mutilating and dismembering the Bomb for fun and profit

== Hushing the Bomb

Apparently Dr. Evil is evil enough to design the Bomb to explode whenever it's run locally. This forces me to connect to the server and risk point deductions whenever I want to test out answers. I'm not going to do that.

First off, running the code offline doesn't actually detonate the Bomb. Like, it's actually offline; what's it gonna do, blow up your computer? Instead, it refuses to run with an `Initialization error: Running on an illegal host [2]`.

While I'll be skipping code explanations, the gist of it is that there are a few functions that check for the presence of a server at localhost (127.0.0.1), and other nefarious things such as checking hostnames. These checks are performed specifically in two functions: `initialize_bomb` and `send_msg`.

Now there are multiple ways to go about avoiding these.

+ Replace calls to these with NOP slides
+ Overwrite the functions themselves with NOP slides
+ Overwrite the first byte of these functions with a `ret` instruction

I took the first option, simply because it was the first option that came to my mind.

There are three spots relevant to the normal control flow where these functions are called:

+ `initialize_bomb` is called in `main`
+ `send_msg` is called in `phase_defused`
+ `send_msg` is called in `explode_bomb`

These three calls were replaced with 0x90 NOP bytes in a hex editor.

Now my Bomb is complacent and doesn't complain about being run offline. You're not evil enough, Dr. Evil.

Later, another student of the class who shall remain anonymous has tipped that instead of outright patching the bomb, it could also be possible to use a debugger to manipulate `rip` to skip over the checks. While this is arguably a quicker solution, I personally found patching the binary to be a more permanent solution.

Also, it may also be possible to make a 'nofail' Bomb - a Bomb that runs connected to the server, notifies when it is defused, but stays quiet just when the answer is wrong. This would require even less patching, as one would only need to patch the `explode_bomb` function. However, I have not attempted this as of now.

== Farming Bombs with auto solvers

Originally I had planned to include here a section on making an automated Bomb Lab solver in Rust. The solver is still under construction. Briefly, the solver will use ELF bindings to patch the bomb as described above, then use the Z3 Theorem Solver from Microsoft Research to automatically deduce answers from the given constraints.

= References

N/A
