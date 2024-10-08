# Problem 2: Extended Sudoku as a CSP

Sudoku is a popular logic-based, combinatorial number-placement puzzle. The classic version consists of a 9 × 9 grid divided into nine 3 × 3 subgrids or blocks. The objective is to fill the grid so that each row, column, and block contains all digits from 1 to 9 exactly once.

You are given an **extended** Sudoku puzzle on a 9 × 9 grid with the following rules:

**Standard Sudoku Rules**:

- Each row must contain the digits 1 through 9 exactly once.
- Each column must contain the digits 1 through 9 exactly once.
- Each of the nine 3 × 3 blocks must contain the digits 1 through 9 exactly once.

**Additional Constraints**:

- The digits on the main diagonal from top-left to bottom-right must contain the digits 1 through 9 exactly once.
- The digits on the anti-diagonal from top-right to bottom-left must contain the digits 1 through 9 exactly once.

## Problem 2a: CSP Modeling [5 points]

Formulate the extended Sudoku puzzle described above as a Constraint Satisfaction Problem (CSP) by specifying the **variables**, **domains**, and **constraints**.

### Problem 2a-1 [1 points]

Define the variables for extended Sudoku.

#### Solution

$X_{ij}$ for $i, j \in \{1, 2, \ldots, 9\}$, representing the value at row $i$ and column $j$

### Problem 2a-2 [1 points]

Define the domains for extended Sudoku.

#### Solution

$$ \{n \in \mathbb{N} \mid 1 \le n \le 9\} = \{1, 2, 3, 4, 5, 6, 7, 8, 9\} $$

### Problem 2a-3 [3 points]

Define the constraints for extended Sudoku.

#### Solution

- $$ \forall i \in \{1, 2, \ldots, 9\}, \{X_{i1}, X_{i2}, \ldots, X_{i9}\} = D $$

    (Each row must contain the digits 1 through 9 exactly once)

- $$ \forall j \in \{1, 2, \ldots, 9\}, \{X_{1j}, X_{2j}, \ldots, X_{9j}\} = D $$

    (Each column must contain the digits 1 through 9 exactly once)

- $$ \forall i \in \{0, 1, 2\}, j \in \{0, 1, 2\}, \{X_{3i+1, 3j+1}, X_{3i+1, 3j+2}, \ldots, X_{3i+3, 3j+3}\} = D $$

    (Each of the nine 3 × 3 blocks must contain the digits 1 through 9 exactly once)

- $$ \{X_{11}, X_{22}, \ldots, X_{99}\} = \{1, 2, \ldots, 9\} $$

    (The digits on the main diagonal from top-left to bottom-right must contain the digits 1 through 9 exactly once)

- $$ \{X_{19}, X_{28}, \ldots, X_{91}\} = \{1, 2, \ldots, 9\} $$

    (The digits on the main diagonal from top-right to bottom-left must contain the digits 1 through 9 exactly once)

## Problem 2b: Solving Strategy [5 points]

Suppose you are solving the extended Sudoku puzzle using the AC-3 algorithm. AC-3 enforces arc consistency by checking all arcs of constraints between variables. When the domain of a variable has values removed, the algorithm revisits the other arcs connected to that variable to ensure consistency.

### Problem 2b-1 [2 points]

Define all the arcs representing constraints between variables in the extended Sudoku puzzle.

Consider both the standard Sudoku constraints (rows, columns, and 3 × 3 blocks) as well as the additional diagonal constraints.

Hint) An arc is a directed pair $(X_i, X_j)$ where $X_i$ and $X_j$ are variables connected by a constraint. For each sudoku constraint, form an arc for every pair.

#### Solution

- **Row Constraints**

    $$ \{(X_{ia}, X_{ib}) \mid i, a, b \in \{1, 2, \ldots, 9\}, a < b\} $$

- **Column Constraints**

    $$ \{(X_{aj}, X_{bj}) \mid j, a, b \in \{1, 2, \ldots, 9\}, a < b\} $$

- **Block Constraints**

    $$ \{(X_{3i+a-3, 3j+b-3}, X_{3i+c-3, 3j+d-3}) \mid i, a, b, c, d \in \{1, 2, 3\}, a < b \lor (a = b \land c < d)\} $$

- **Main Diagonal Constraints**

    $$ \{(X_{aa}, X_{bb}) \mid a, b \in \{1, 2, \ldots, 9\}, a < b\} $$

- **Anti-Diagonal Constraints**

    $$ \{(X_{a, 10-a}, X_{b, 10-b}) \mid a, b \in \{1, 2, \ldots, 9\}, a < b\} $$

### Problem 2b-2 [3 points]

While AC-3 is useful for enforcing local consistency, it may have limitations in solving more complex puzzles like the extended Sudoku. One alternative approach is using **K-consistency**. In K-consistency, any consistent assignment to $k-1$ variables can be extended to the $k$ th variable in a way that satisfies the constraints for $k$ variables.

1. Briefly describe one potential limitation of the AC-3 algorithm when applied to extended Sudoku [1 points]

2. Reformulate the constraints from Problem 2a-3 in **n-ary** form to make them suitable for use in a K-consistency algorithm. [2 points]

Hint) When writing n-ary constraints, use the expression `AllDifferent(Vars)` to describe that all variables in `Vars` differ from one another.

#### Solution

1. AC-3 only ensures binary constraints between pairs of variables are satisfied, which while on the surface may seem implying of the CSP's solvability, in actuality may not be sufficient for the rather complex constraints of extended Sudoku. Arc consistency does not account for the overall structure of the problem or higher-order constraints that may exist among three or more variables, thus it does not guarantee a solution for this particular CSP.

2. Constraints:

    - `AllDifferent(Row_i)` for each row $i$
    - `AllDifferent(Column_j)` for each column $j$
    - `AllDifferent(Block_{k})` for each 3 × 3 block $k$
    - `AllDifferent(Diagonal_1)` for the main diagonal from top-left to bottom-right
    - `AllDifferent(Diagonal_2)` for the anti-diagonal from top-right to bottom-left
