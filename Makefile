.PHONY: all clean

SRC_DIR = src
BUILD_DIR = build

FILES_SERVER = $(wildcard $(SRC_DIR)/server/*.cpp)
OBJECTS_SERVER = $(FILES_SERVER:$(SRC_DIR)/server/%.cpp=$(BUILD_DIR)/server/%.o)
FILES_CLIENT = $(wildcard $(SRC_DIR)/client/*.cpp)
OBJECTS_CLIENT = $(FILES_CLIENT:$(SRC_DIR)/client/%.cpp=$(BUILD_DIR)/client/%.o)

CXX = g++
CXX_FLAGS = -std=c++17 -Wall -Wextra -Werror -Wunused

all: client server

client: $(OBJECTS_CLIENT)
	$(CXX) $(CXX_FLAGS) -o $@ $^ -lstdc++ -lpthread

server: $(OBJECTS_SERVER)
	$(CXX) $(CXX_FLAGS) -o $@ $^ -lstdc++ -lpthread

$(BUILD_DIR)/client/%.o: $(SRC_DIR)/client/%.cpp
	@mkdir -p $(BUILD_DIR)/client
	$(CXX) $(CXX_FLAGS) -c $< -o $@

$(BUILD_DIR)/server/%.o: $(SRC_DIR)/server/%.cpp
	@mkdir -p $(BUILD_DIR)/server
	$(CXX) $(CXX_FLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) client server
