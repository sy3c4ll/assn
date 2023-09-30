#set page(
    paper: "a4",
    margin: (top: 3.0cm, rest: 2.54cm)
)
#set par(
    justify: true,
    leading: 1.0em,
)
#set text(
    font: "Malgun Gothic",
    size: 10pt,
    hyphenate: false,
)
#set heading(numbering: "1. ")
#show heading: set text(size: 12pt)

#align(center, text(size: 16pt)[
    *2023 Fall OOP Assignment Report*
])
#align(right, text(size: 11pt)[
    과제 번호 : 1 \
    학번 : 20230262 \
    이름 : 김연웅 \
    Povis ID : yeonung04 \
])
#rect(width: 100%, align(center)[
    #set par(justify: false, leading: 1.08em)
    #block(spacing: 1.08em + 8pt)[
        *명예서약 (Honor Code)*
    ]
    나는 이 프로그래밍 과제를 다른 소스를 인용없이 참고하거나, \
    다른 사람의 부적절한 도움을 받지 않고 완수하였습니다. \
    I completed this programming task without using any uncited sources \
    or receiving improper help from others. \
])

/* 프로그램을 하다 보면 결정해야 할 세부 사항이 많은데,
 * 이러한 세부 사항을 처리한 방법과 이유를 보고서에 쓰십시오.
 * 독창적인 아이디어와 추가 기능은 보너스 점수를 받을 수 있으므로,
 * 보고서에 명확히 기재하십시오. 문제가 여러 개인 경우,
 * 각 문제별로 보고서를 별도로 작성합니다.
 */

= 프로그램 구조 및 알고리즘 (5점)

/* - 제출한 프로그램의 개요와 전체적인 구조를 작성.
 * - Class를 작성한 경우, 각 Class에 대해 소개하고 Class들의 관계에 대해 설명.
 * - 프로그램 내 각 파일에 포함된 중요 함수와 변수에 대해, 어떤 기능을 수행하고 어떤 의미를
 *   가지는지 작성.
 * - 전체적인 알고리즘에 대한 설명.
 * - 특히 고민을 많이 하여 창의적이고 효율적인 논리를 적용했다면, 그에 대한 설명.
 */

The code employs a brute-force approach to solving the problem, rotating through the array and filling every node with the appropriate value in order. The code is broadly divided into three parts: receiving input, filling the array and printing. Each functionality is handled by functions `main`, `solve` and `print` respectively.

== `main`

In `main`, the entrypoint of the program, input is received in one of two ways, which are mutually exclusive. Should the user pass command-line arguments into the program, the program will expect these values to be N, M, S and D respectively and process a single output, which is sent to `stdout`. This is useful for quick testing and overall improves accessibility. Otherwise, the program will read from `input.txt` and write to `output.txt`. This is useful for batch processing and is the default behavior. All errors are sent to `stderr`.

For the former method, the program assumes four integers as command-line arguments, which if not satisfied results in undefined behaviour. The four arguments are parsed with `std::atoi` and stored as `N`, `M`, `S` and `D` respectively. Input value validation is performed via an inline helper function to verify the values fall within the range given through the problem statement, which if failed exits the program with an error message. The program then calls `solve` with the four values and prints the result to `stdout`.

For the latter method, C-style IO is utilised to minimise performance overhead from `iostream`. Four integers are read while `fscanf` does not return `EOF`, which are stored as `N`, `M`, `S` and `D` respectively. Input validation is performed with every pair, however every failed pair results not in a program termination but an error to `stderr` and a skip. The program then calls `solve` with the four values and prints the result to `output.txt`. Since the operand array is initialised once at program start to minimise allocation syscalls, the program must reset the array to zero before each call to `solve`. This is done with `memset`.

== `solve`

This method takes a two-dimensional array, `N`, `M`, `S` and `D` as its arguments. Variables `cx` and `cy` are created to store the cursor coordinates, and `dir` to store the current direction of cursor movement. Compile-time constants `dx` and `dy` are created to allow easy access to increments to $x$- and $y$-coordinates as `dx[dir]` and `dy[dir]` respectively with minimal overhead in performance. A loop is then run for `N`$times$`M` iterations, with `i` keeping track of the current iteration. Every iteration the cell under the cursor is filled as $S + D i$. The next cursor position is precalculated, which is then checked to see if it is unoccupied and within bounds. If invalid, the cursor direction is rotated clockwise. The cursor is then moved to the next position and the loop continues until the entire array is filled.

== `print`

This method takes a file pointer, a two-dimensional array and `N` and `M` as its arguments. The function prints the array, bounded by `N`$times$`M`, to the file pointer in the format specified by the problem statement, iterating through the array and printing each value, followed by a newline.

== Enhancements

- The functionality of the program has been extended to allow for command-line arguments, which if passed will be used instead of reading from `input.txt` and writing to `output.txt`.
- The program will now print helpful error messages to `stderr`, which will be displayed on the terminal regardless of whether `output.txt` is being used. This separates error messages from results, and can help with both debugging and producing useful results from batch processing disregarding all errors.

= 토론 및 개선 (5점)

/* - 이번 과제를 통하여 배우거나 깨달은 내용 정리.
 * - 혹시 과제를 완벽히 하지 못했다면 본인이 구현하지 못한 부분을 설명.
 * - 제작된 프로그램에 추가할 수 있는 기능, 실행 속도를 높이는 방법 등 프로그램의 성능을
 *   높일 수 있는 방법에 대하여 설명.
 */

The `solve` and `print` functions are inflexible in the extreme due to requiring an `int(*)[10]` as input. No constants are used to control the maximum array width, such that the user is expected to resize the input array manually to fit the argument type. This is a poor design choice. The problem may be alleviated in one of two ways: either by using nested `std::vector`s or by using a template. The former is the simpler solution that may even allow the removal of arguments `N` and `M`, however incurs a performance penalty due to dynamically allocating memory at runtime. The latter incurs minimal performance penalties due to compile-time polymorphism, however complicates function calls due to the need to specify template arguments. In the latter case, raw pointers may also optionally be replaced with references to nested STL `array`s, which may improve readability while also improving security by disallowing random memory access through faulty pointers.

= 참고 문헌

/* - 인터넷 등의 다른 소스에서 참고한 내용이 있으면 출처와 내용을 명확히 기술.
 *   #text(color: red, rect[
 *      숙제를 위하여 다른 소스를 참고하고 하는 것은 좋으나, 그 경우에 반드시 출처를 명시
 *      해야 한다. 출처가 명시되어 있지 않은 경우는 부정행위로 간주될 수 있다.
 *   ])
 * - 함께 토의한 친구가 있다면 학번과 이름을 기재.
 */

[1] 04. Compound Types - Sunghyun Cho, Spring 2023 \
[2] #link("https://cplusplus.com/reference/cstdio/FILE/")[cplusplus.com/reference/cstdio/FILE/] - cplusplus.com \
[3] #link("https://cplusplus.com/reference/cstdlib/atoi/")[cplusplus.com/reference/cstdlib/atoi] - cplusplus.com \
[4] #link("https://cplusplus.com/reference/cstring/memset/")[cplusplus.com/reference/cstring/memset/] - cplusplus.com \
[5] #link("https://en.cppreference.com/w/cpp/language/constexpr")[constexpr specifier (since C++11)] - cppreference.com \
[6] #link("https://typst.app")[Typst: Compose papers faster] - Typst \