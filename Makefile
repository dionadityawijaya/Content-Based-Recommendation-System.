CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
SRC_DIR = src
INC_DIR = include
TEST_DIR = tests
BUILD_DIR = build

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))
TESTS = $(wildcard $(TEST_DIR)/*.cpp)

all: recommender test

recommender: $(OBJS)
    $(CXX) $(CXXFLAGS) -o $(BUILD_DIR)/$@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
    $(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

test: $(OBJS)
    $(CXX) $(CXXFLAGS) -I$(INC_DIR) $(TESTS) $(OBJS) -o $(BUILD_DIR)/$@ && $(BUILD_DIR)/test

clean:
    rm -rf $(BUILD_DIR)/*.o $(BUILD_DIR)/recommender $(BUILD_DIR)/test
