CXX = g++
CXXFLAGS = -std=c++17 -O3 -march=native -Iinclude -I/usr/include/eigen3
LDFLAGS = -lgtest -lgtest_main -lpthread

SRC_DIR = src
TEST_DIR = tests
BUILD_DIR = build

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

TEST_SRC = $(TEST_DIR)/test_main.cpp
TEST_OBJ = $(BUILD_DIR)/test_main.o
TEST_EXE = $(BUILD_DIR)/gauss_tests

MAIN_EXE = $(BUILD_DIR)/gauss_solver

all: $(MAIN_EXE) $(TEST_EXE)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(MAIN_EXE): $(OBJS) $(BUILD_DIR)/main.o
	$(CXX) $(CXXFLAGS) $^ -o $@

$(TEST_EXE): $(filter-out $(BUILD_DIR)/main.o,$(OBJS)) $(TEST_OBJ)
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@

test: $(TEST_EXE)
	./$(TEST_EXE)

run: $(MAIN_EXE)
	./$(MAIN_EXE)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all test run clean