CXX := g++
RM := rm -rf
MD := mkdir -p

CXXFLAGS := -std=c++20 -Wall -Wextra -pedantic -O2 -g
LDFLAGS :=

SRCDIR := src
OBJDIR := build/obj
BINDIR := build/bin

SRC := ${wildcard ${SRCDIR}/*.cpp}
OBJ := ${patsubst ${SRCDIR}/%.cpp,${OBJDIR}/%.o,${SRC}}
BIN := ${BINDIR}/assn

.PHONY: all build run clean

all: build

build: ${BIN}

${BIN}: ${OBJ} | ${BINDIR}
	${CXX} ${LDFLAGS} -o${BIN} $^

${OBJDIR}/%.o: ${SRCDIR}/%.cpp | ${OBJDIR}
	${CXX} ${CXXFLAGS} -c -o$@ $<

${OBJDIR}:
	${MD} $@

${BINDIR}:
	${MD} $@

run: ${BIN}
	./$< ${ARGS}

clean:
	${RM} ${OBJDIR}
	${RM} ${BINDIR}
