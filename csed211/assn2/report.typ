#let title = [CSED211: Lab Report]

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
  2024-XX-XX/2024-XX-XX \
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

= Conclusion

= References
