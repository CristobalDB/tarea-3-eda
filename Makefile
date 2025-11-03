# === Toolchain ===
CXX      = g++
CXXFLAGS = -std=c++11 -O2 -Wall -Wextra -Iinclude
LDFLAGS  =

# === App (REPL) ===
APP_SRC = src/main.cpp src/Tokenizer.cpp src/InfixToPostfix.cpp src/PostfixEval.cpp src/ExprTree.cpp
APP_OBJ = $(APP_SRC:.cpp=.o)
APP_BIN = bin/calculadora

# === Tests TAD propios (LinkedList/Stack header-only) ===
TAD_TEST_SRC = src/tests_tads.cpp
TAD_TEST_OBJ = $(TAD_TEST_SRC:.cpp=.o)
TAD_TEST_BIN = bin/tests_tads

# === ADTs del libro (namespace eda) ===
# Coloca stack.cpp y queue.cpp en src/lLists, y sus headers en include/lLists
L_ADT_SRC = src/lLists/stack.cpp src/lLists/queue.cpp
L_ADT_OBJ = $(L_ADT_SRC:.cpp=.o)

# Test de paréntesis del libro
PAREN_TEST_SRC = src/tests_parenthesis.cpp
PAREN_TEST_OBJ = $(PAREN_TEST_SRC:.cpp=.o)
PAREN_TEST_BIN = bin/test_parenthesis

# === Default ===
all: $(APP_BIN)

# === Link: App ===
$(APP_BIN): $(APP_OBJ)
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# === Link: Tests TAD propios ===
tests: $(TAD_TEST_BIN)

$(TAD_TEST_BIN): $(TAD_TEST_OBJ)
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# === Link: Test paréntesis (usa ADTs del libro) ===
test_paren: $(L_ADT_OBJ) $(PAREN_TEST_OBJ)
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) -o $(PAREN_TEST_BIN) $(L_ADT_OBJ) $(PAREN_TEST_OBJ) $(LDFLAGS)

# === Compile rules ===
# Compila cualquier .cpp a .o con -Iinclude (sirve para include/lLists/* también)
src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Test tokenizer
TEST_TOK_SRC = src/test_tokenizer.cpp src/Tokenizer.cpp
TEST_TOK_BIN = bin/test_tokenizer
test_tok: $(TEST_TOK_SRC)
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) -o $(TEST_TOK_BIN) $(TEST_TOK_SRC)

# === Test Infix->Postfix ===
TEST_IN2POS_SRC = src/test_in2pos.cpp src/Tokenizer.cpp src/InfixToPostfix.cpp
TEST_IN2POS_BIN = bin/test_in2pos

test_in2pos: $(TEST_IN2POS_SRC)
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) -o $(TEST_IN2POS_BIN) $(TEST_IN2POS_SRC)

# === Test evaluación postfix ===
TEST_EVAL_SRC = src/test_eval.cpp src/Tokenizer.cpp src/InfixToPostfix.cpp src/PostfixEval.cpp
TEST_EVAL_BIN = bin/test_eval

test_eval: $(TEST_EVAL_SRC)
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) -o $(TEST_EVAL_BIN) $(TEST_EVAL_SRC)


# === Clean ===
clean:
	rm -rf $(APP_OBJ) $(TAD_TEST_OBJ) $(L_ADT_OBJ) $(PAREN_TEST_OBJ) \
	       $(APP_BIN) $(TAD_TEST_BIN) $(PAREN_TEST_BIN)

.PHONY: all tests test_paren clean
