CXX := g++
RM := rm -f
CXXFLAGS := -std=c++11 -Wall -Wextra -pedantic -O3 -g

SRC := pa1 utils
BIN := pa1

.PHONY: all clean

all: $(BIN)

clean:
	$(RM) $(BIN) $(addsuffix .o, $(SRC))

$(BIN): $(SRC:=.cpp)
	$(CXX) $(CXXFLAGS) -o$(BIN) $(SRC:=.cpp)