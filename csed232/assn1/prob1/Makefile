CXX := g++
TYP := typst compile
RM := rm -f
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic -g -O2

SRC := prob1_sol1 prob1_sol2
DOC := report

.PHONY: all doc clean

all: ${SRC} doc

doc: ${DOC:=.typ}
	${TYP} ${DOC:=.typ}

clean:
	${RM} ${SRC} ${DOC:=.pdf}

%: %.cpp
	${CXX} ${CXXFLAGS} -o$@ $<
