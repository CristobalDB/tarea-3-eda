CXX      = g++
CXXFLAGS = -std=c++11 -O2 -Wall -Wextra -Iinclude
LDFLAGS  =

APP_SRC = src/main.cpp \
          src/Tokenizer.cpp \
          src/InfixToPostfix.cpp \
          src/PostfixEval.cpp \
          src/ExprTree.cpp

APP_OBJ = $(APP_SRC:.cpp=.o)
APP_BIN = bin/calculadora

all: $(APP_BIN)

$(APP_BIN): $(APP_OBJ)
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(APP_OBJ) $(APP_BIN)

.PHONY: all clean
