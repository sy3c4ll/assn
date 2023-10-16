CXX := g++
TYP := typst compile
RM := rm -f
RD := rm -rf
MD := mkdir -p

CXXFLAGS := -std=c++20 -Wall -Wextra -pedantic -O2 -g
LDFLAGS :=

SRCDIR := src
DOCDIR := doc
OBJDIR := build/obj
BINDIR := build/bin

SRC := ${wildcard ${SRCDIR}/*.cpp}
DOC := ${wildcard ${DOCDIR}/*.typ}
OBJ := ${patsubst ${SRCDIR}/%.cpp,${OBJDIR}/%.o,${SRC}}
BIN := ${BINDIR}/assn

.PHONY: all doc build run clean

all: doc build

doc: ${DOC:.typ=.pdf}

${DOCDIR}/%.pdf: ${DOCDIR}/%.typ
	${TYP} $<

build: ${OBJ} ${BINDIR}
	${CXX} ${LDFLAGS} -o${BIN} ${OBJ}

${OBJDIR}/%.o: ${SRCDIR}/%.cpp ${OBJDIR}
	${CXX} ${CXXFLAGS} -c -o$@ $<

${OBJDIR}:
	${MD} $@

${BINDIR}:
	${MD} $@

run: ${BIN}
	./$<

${BIN}: build

clean:
	${RD} ${OBJDIR}
	${RD} ${BINDIR}
	${RM} ${DOC:.typ=.pdf}