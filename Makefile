# C++ 컴파일러
CC = g++

# C++ 컴파일러 옵션
CXXFLAGS = -g -std=c++17 -pthread

# 링커 옵션
LDFLAGS = 

# Library
LIBS = -lurcu

# 소스 파일 디렉토리
SRC_DIR = .

# 오브젝트 파일 디렉토리
OBJ_DIR = Objs

# Include 파일 디렉토리
INCLUDE = -I $(SRC_DIR)
#INCLUDE = -I EWAPP EWFW EWLIB

# 생성하고자 하는 실행 파일 이름
TARGET = main

# EWLIB/Task
SRCS += $(wildcard $(SRC_DIR)/EWLIB/*.cpp)
SRCS += $(wildcard $(SRC_DIR)/EWLIB/Task/Thread/*.cpp)
SRCS += $(wildcard $(SRC_DIR)/EWLIB/Task/Process/*cpp)
SRCS += $(wildcard $(SRC_DIR)/EWLIB/Communication/IPC/*.cpp)
SRCS += $(wildcard $(SRC_DIR)/EWLIB/Communication/Ethernet/TCP/*.cpp)
SRCS += $(wildcard $(SRC_DIR)/EWLIB/Communication/Ethernet/UDP/*.cpp)
SRCS += $(wildcard $(SRC_DIR)/EWLIB/Container/*cpp)
SRCS += $(wildcard $(SRC_DIR)/EWLIB/FileIO/*cpp)

# Main
SRCS += $(wildcard $(SRC_DIR)/*.cpp)


OBJS = ${SRCS:.cpp=.o}
DEPS = $(OBJS:.o=.d)

OBJECTS = $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(SRCS))

all: main
$(OBJ_DIR)/%.o : $(SRCS)
	mkdir -p $(shell dirname $@) 
	$(CC) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

$(TARGET) : $(OBJECTS)
	$(CC) $(CXXFLAGS) $(INCLUDE) $(SRCS) -o  $(TARGET) $(LDFLAGS) 

.PHONY: clean all
clean:
	rm -f $(OBJECTS) $(TARGET)

-include $(DEPS)
