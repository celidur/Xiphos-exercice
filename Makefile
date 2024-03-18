.PHONY: all clean

SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin

FILES_SERVER = $(wildcard $(SRC_DIR)/server/*.cpp)
OBJECTS_SERVER = $(FILES_SERVER:$(SRC_DIR)/server/%.cpp=$(BUILD_DIR)/%.o)
FILES_CLIENT = $(wildcard $(SRC_DIR)/client/*.cpp)
OBJECTS_CLIENT = $(FILES_CLIENT:$(SRC_DIR)/client/%.cpp=$(BUILD_DIR)/%.o)

CXX = g++
CXX_FLAGS = -std=c++20 -Wall -Wextra -Werror -Wunused

all: $(BIN_DIR)/client $(BIN_DIR)/server

$(BIN_DIR)/client: $(OBJECTS_CLIENT)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXX_FLAGS) -o $@ $^ -lstdc++

$(BIN_DIR)/server: $(OBJECTS_SERVER)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXX_FLAGS) -o $@ $^ -lstdc++

$(BUILD_DIR)/%.o: $(SRC_DIR)/client/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXX_FLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/server/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXX_FLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)
