#let title = [CSED103 Fall '24: Assignment \#1]

#set page(
  paper: "a4",
  header: align(right + horizon, title),
  numbering: "- 1 / 1 -",
)
#set par(justify: true)
#set text(
  font: "Source Han Serif K",
  size: 11pt,
  hyphenate: false,
)
#set heading(numbering: "I a. ")
#show raw: set text(font: "Sarasa Mono K")

#align(center, text(size: 24pt, weight: "bold",
  title
))
#align(right, text(style: "italic")[
  2024-09-27/2024-10-10 \
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

= Usage

= Implementation

= Screenshots

= Discussion

= Conclusion

= References
