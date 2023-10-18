CXX := g++
RM := rm -rf
MD := mkdir -p

CXXFLAGS := -std=c++11 -Wall -Wextra -pedantic -O2 -g
LDFLAGS :=

SRCDIR := .
OBJDIR := build
BINDIR := .

SRC := pa2 utils tree heap
BIN := pa2

.PHONY: all run eval clean

all: ${BINDIR}/${BIN}

${BINDIR}/${BIN}: ${patsubst %,${OBJDIR}/%.o,${SRC}} | ${BINDIR}
	${CXX} ${LDFLAGS} -o$@ $^

${OBJDIR}/%.o: ${SRCDIR}/%.cpp | ${OBJDIR}
	${CXX} ${CXXFLAGS} -c -o$@ $<

${OBJDIR}:
	${MD} $@

${BINDIR}:
	${MD} $@

run: ${BINDIR}/${BIN}
	./$< ${ARGS}

eval: ${BINDIR}/evaluate
	./$< ${ARGS}

${BINDIR}/evaluate: ${SRCDIR}/evaluate.cpp | ${BINDIR}
	${CXX} ${CXXFLAGS} -o$@ $<

clean:
	${RM} ${patsubst %,${OBJDIR}/%.o,${SRC}} ${BINDIR}/${BIN} ${BINDIR}/evaluate