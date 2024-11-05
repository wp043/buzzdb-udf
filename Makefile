# Top-level Makefile for BuzzDB with UDF Support

# Compiler and Flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Werror -I./src/include

# Directories
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin
TEST_DIR = test
UDF_EXAMPLES_DIR = $(SRC_DIR)/udf_examples

# Source Files
SRC_FILES = $(wildcard $(SRC_DIR)/*/*.cpp) $(SRC_DIR)/main.cpp
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))

# Executable
TARGET = $(BIN_DIR)/buzzdb

# UDFs
UDF_LIBS = $(wildcard $(UDF_EXAMPLES_DIR)/*.so)

# Tests
TEST_SRC_FILES = $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJ_FILES = $(patsubst $(TEST_DIR)/%.cpp,$(BUILD_DIR)/test/%.o,$(TEST_SRC_FILES))
TEST_TARGET = $(BIN_DIR)/udf_test

# Default Rule
all: directories $(TARGET) $(UDF_LIBS)

# Create Necessary Directories
directories:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR)/catalog
	@mkdir -p $(BUILD_DIR)/execution
	@mkdir -p $(BUILD_DIR)/expression
	@mkdir -p $(BUILD_DIR)/parser
	@mkdir -p $(BUILD_DIR)/common
	@mkdir -p $(BUILD_DIR)/storage
	@mkdir -p $(BUILD_DIR)/udf_examples
	@mkdir -p $(BUILD_DIR)/test
	@mkdir -p $(BIN_DIR)

# Build the BuzzDB Executable
$(TARGET): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile Source Files into Object Files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Build UDF Shared Libraries
$(UDF_EXAMPLES_DIR)/%.so: $(UDF_EXAMPLES_DIR)/%.cpp
	$(CXX) -std=c++11 -shared -fPIC -o $@ $< -I$(SRC_DIR)/include

# Build and Run Tests
test: $(TEST_TARGET)
	./scripts/run_tests.sh

$(TEST_TARGET): $(TEST_OBJ_FILES) $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BUILD_DIR)/test/%.o: $(TEST_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Clean Build Artifacts
clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(BIN_DIR)
	rm -f $(UDF_EXAMPLES_DIR)/*.so

# Phony Targets
.PHONY: all directories clean test