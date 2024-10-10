#import "@preview/fletcher:0.5.1" as fletcher: diagram, node, edge

#let title = [CSED103 Fall '24: Assignment \#1]

#set page(
  paper: "a4",
  header: align(right + horizon, title),
  numbering: "- 1 / 1 -",
)
#set par(justify: true)
#set text(
  font: "Source Han Serif K",
  size: 10pt,
  hyphenate: false,
)
#set heading(numbering: "I a. ")
#show raw: set text(font: "Sarasa Mono K")
#show link: underline

#align(center, text(size: 24pt, weight: "bold",
  title
))
#align(right, text(style: "italic")[
  2024-09-26/2024-10-10 \
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
#show: rest => columns(2, rest)

= Overview

This program implements Kuhn Poker as described in the assignment. It implements a menu screen, in which the player may choose to print the rules, play the game or exit the program. It also implements the game itself, which is played between the player and the computer. The player may choose to check, fold, call or raise. The computer will play random moves. The game ends when either player folds, or when both the player and the computer confirm on the pot. The winner is determined by the hand strength of the two players. The player is automatically sent to the menu screen after the game.

The following is a structure diagram describing the high-level architecture of the program:

= Usage

The program is a single C99 file (assn1.c), and can be compiled and run trivially. On execution, follow the on-screen instructions.

== Unix/Linux

=== Prerequisites

GCC or Clang

=== Compiling

With GCC:

`gcc -std=c99 -oassn1 assn1.c`

Or with Clang:

`clang -std=c99 -oassn1 assn1.c`

=== Running

`./assn1`

== Windows

=== Prerequisites

MSVC, or alternatively GCC via MinGW

=== Compiling

With MSVC, in the Visual Studio Developer Powershell:

`cl.exe assn1.c`

Or with MinGW GCC, in MinGW bash:

`gcc.exe -std=c99 -oassn1.exe assn1.c`

=== Running

`./assn1.exe`

= Implementation

= Screenshots

#figure(image("img/1.png"), caption: [Before compilation])

#figure(image("img/2.png"), caption: [On compilation])

#figure(image("img/3.png"), caption: [On execution])

#figure(image("img/4.png"), caption: [Game rules])

#figure(image("img/5.png"), caption: [On invalid input])

#figure(image("img/6.png"), caption: [On game start])

#figure(image("img/7.png"), caption: [On round end])

#figure(image("img/8.png"), caption: [On game end])

#figure(image("img/9.png"), caption: [Returning to menu])

#figure(image("img/10.png"), caption: [On exit])

= Discussion

== Points of interest

It was of particular interest to implement receiving then verifying single-character inputs without using strings. While normally the writer would consider using `fgets` and `strcmp` for the task, it proved an interesting challenge to implement this with only single characters, and the resulting code unexpectedly became to be quite elegant as well. The following is what the writer has ultimately settled on:

```c
while ((unsigned) (op = getchar()) -  '1' >= 3 || getchar() != '\n') {
  if (op != '\n')
    while (getchar() != '\n');
  printf("Message for invalid input");
}
```

As one can observe, single `getchar` calls are used to ensure that the input is exactly '1'..='3', followed by a newline. The first `getchar` call is also stored inline, for later use. Then `getchar` is used repeatedly not for input, but to clear the input buffer until a newline is encountered. This however yields the problem of a single newline input hanging the program, which is solved by checking against that specific case. This is a simple yet elegant solution despite the relative complexity of the situation that the writer is quite proud of.

== Room for improvement

Modularising the code such that input, output and game logic are separated into distinct files would make the code more readable and maintainable. This would also allow for easier testing and debugging.

The program relies on `system` for clearing the screen, which is not portable. This could be fixed by using a `curses`-derivative console manipulation library such as `notcurses` or by implementing a portable solution. The writer has personally created a portable drop-in replacement for #link("https://github.com/sy3c4ll/conio-cpp")[`conio.h` in C++11] that uses system libraries for each platform to achieve the same effect, trivially modifiable to be used in C code. This may prove useful in creating simple portable solutions without the need for a full-blown console manipulation library.

But why stop there? Manipulating terminal _emulators_ is a fundamentally legacy solution to a modern problem. A more modern solution would be to use a GUI library such as `Dear ImGui` or `GTK` to create a graphical interface. This would allow for a more user-friendly interface, and would also allow for more complex games to be implemented. The writer has particularly found `GTK` a delight to work with, with its elegant way of mimicking the object-oriented paradigm in C.

The game could even be further expanded to include more players, or even a networked multiplayer mode. This would require a complete rewrite of the game logic, but would be a fun exercise in network programming.

== Challenges faced

Strings in C are arrays of single-byte ASCII characters. This may make strings simple to deal with, however the lack of built-in support for Unicode makes it difficult to ensure functionality on all environments, since the program prints CJK characters and symbols such as the filled and unfilled box. Currently the program dumps bytes as stored in the source file, which is in UTF-8, and hopes that the target terminal can print UTF-8 bytes correctly. However, with the ubiquity of UTF-8 not yet quite there (I have personally seen professors and TAs hand out template code in EUC-KR), this can hardly be guaranteed. Overall the situation is a big mess and I have yet to find a reasonable solution to this decades-old problem.

= Conclusion

Implementing Kuhn Poker was a fun exercise in C programming. The writer has learned a lot about C programming, and has also learned a lot about the game of Kuhn Poker. The writer has also learned a lot about the limitations of C programming, and has also learned a lot about the limitations of Kuhn Poker as a game. The writer has also learned a lot about the limitations of the writer, and has also learned a lot about the limitations of the writer's patience. The writer has also learned a lot about the limitations of the writer's ability to write a conclusion.

= References

- #link("https://en.wikipedia.org/wiki/Kuhn_poker")[Kuhn Poker - Wikipedia]
- #link("https://en.cppreference.com/w/c/language/operator_precedence")[C Operator Precedence - cppreference.com]
