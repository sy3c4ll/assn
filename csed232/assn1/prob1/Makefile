CXX := g++
RM := rm -f
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic -g -O2

SRC := prob1_sol1 prob1_sol2

.PHONY: all clean

all: ${SRC}

%: %.cpp
	${CXX} ${CXXFLAGS} -o$@ $<

clean:
	${RM} ${SRC}
