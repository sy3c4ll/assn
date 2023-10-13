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

= 토론 및 개선 (5점)

/* - 이번 과제를 통하여 배우거나 깨달은 내용 정리.
 * - 혹시 과제를 완벽히 하지 못했다면 본인이 구현하지 못한 부분을 설명.
 * - 제작된 프로그램에 추가할 수 있는 기능, 실행 속도를 높이는 방법 등 프로그램의 성능을
 *   높일 수 있는 방법에 대하여 설명.
 */

= 참고 문헌

/* - 인터넷 등의 다른 소스에서 참고한 내용이 있으면 출처와 내용을 명확히 기술.
 *   #text(color: red, rect[
 *      숙제를 위하여 다른 소스를 참고하고 하는 것은 좋으나, 그 경우에 반드시 출처를 명시
 *      해야 한다. 출처가 명시되어 있지 않은 경우는 부정행위로 간주될 수 있다.
 *   ])
 * - 함께 토의한 친구가 있다면 학번과 이름을 기재.
 */