# Variáveis
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic
INCLUDES = -Iinclude
SRC_DIR = src
TEST_DIR = tests
OBJ_DIR = obj
BIN_DIR = bin

# Arquivos fonte e objetos
SRCS = $(wildcard $(SRC_DIR)/dominios/*.cpp)
TEST_SRCS = $(wildcard $(TEST_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
TEST_OBJS = $(TEST_SRCS:$(TEST_DIR)/%.cpp=$(OBJ_DIR)/%.o)
DEPS = $(OBJS:.o=.d) $(TEST_OBJS:.o=.d)

# Executável
TARGET = $(BIN_DIR)/runTests

# Regras
all: $(TARGET)

$(TARGET): $(OBJS) $(TEST_OBJS) | $(BIN_DIR)
    $(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
    $(CXX) $(CXXFLAGS) $(INCLUDES) -MMD -c $< -o $@

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp | $(OBJ_DIR)
    $(CXX) $(CXXFLAGS) $(INCLUDES) -MMD -c $< -o $@

$(OBJ_DIR) $(BIN_DIR):
    mkdir -p $@

-include $(DEPS)

clean:
    rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean# Variáveis
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic
INCLUDES = -Iinclude
SRC_DIR = src
TEST_DIR = tests
OBJ_DIR = obj
BIN_DIR = bin

# Arquivos fonte e objetos
SRCS = $(wildcard $(SRC_DIR)/dominios/*.cpp)
TEST_SRCS = $(wildcard $(TEST_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
TEST_OBJS = $(TEST_SRCS:$(TEST_DIR)/%.cpp=$(OBJ_DIR)/%.o)
DEPS = $(OBJS:.o=.d) $(TEST_OBJS:.o=.d)

# Executável
TARGET = $(BIN_DIR)/runTests

# Regras
all: $(TARGET)

$(TARGET): $(OBJS) $(TEST_OBJS) | $(BIN_DIR)
    $(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
    $(CXX) $(CXXFLAGS) $(INCLUDES) -MMD -c $< -o $@

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp | $(OBJ_DIR)
    $(CXX) $(CXXFLAGS) $(INCLUDES) -MMD -c $< -o $@

$(OBJ_DIR) $(BIN_DIR):
    mkdir -p $@

-include $(DEPS)

clean:
    rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean