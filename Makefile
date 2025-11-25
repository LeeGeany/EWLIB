# C++ 컴파일러
CC = g++
#CC = aarch64-linux-gnu-g++

# C++ 컴파일러 옵션
CXXFLAGS = -g -std=c++17 -pthread

FFTW_PREFIX = /usr/local/fftw-x86

# Library
#LIBS += -lurcu
LIBS += -L$(FFTW_PREFIX)/lib -lfftw3 -lm
#LIBS += -L/usr/local/fftw-arm64/lib -lfftw3 -lm

# Include 파일 디렉토리
INCLUDE += -I$(SRC_DIR)
INCLUDE += -I$(FFTW_PREFIX)/include
#INCLUDE += -I/usr/local/fftw-arm64/include
#INCLUDE = -I EWAPP EWFW EWLIB

# 링커 옵션
LDFLAGS = -Wl,-rpath,$(FFTW_PREFIX)/lib

# 소스 파일 디렉토리
SRC_DIR = .

# 오브젝트 파일 디렉토리
OBJ_DIR = Objs

# 생성하고자 하는 실행 파일 이름
TARGET = main

# EWLIB
#SRCS += $(wildcard $(SRC_DIR)/EWLIB/Communication/Ethernet/TCP/*.cpp)
#SRCS += $(wildcard $(SRC_DIR)/EWLIB/Communication/Ethernet/UDP/*.cpp)
SRCS += $(wildcard $(SRC_DIR)/EWLIB/Communication/Event/Epoll/*.cpp)
SRCS += $(wildcard $(SRC_DIR)/EWLIB/Communication/Event/Signal/*.cpp)
SRCS += $(wildcard $(SRC_DIR)/EWLIB/Communication/IPC/MsgQ/*.cpp)

SRCS += $(wildcard $(SRC_DIR)/EWLIB/Container/*cpp)

SRCS += $(wildcard $(SRC_DIR)/EWLIB/FileIO/Dir/*cpp)
SRCS += $(wildcard $(SRC_DIR)/EWLIB/FileIO/File/*cpp)
SRCS += $(wildcard $(SRC_DIR)/EWLIB/FileIO/FIO/*cpp)

SRCS += $(wildcard $(SRC_DIR)/EWLIB/Sync/Lock/*.cpp)
SRCS += $(wildcard $(SRC_DIR)/EWLIB/Sync/Mutex/*.cpp)
SRCS += $(wildcard $(SRC_DIR)/EWLIB/Sync/Spinlock/*.cpp)
SRCS += $(wildcard $(SRC_DIR)/EWLIB/Sync/Waiter/*.cpp)

SRCS += $(wildcard $(SRC_DIR)/EWLIB/Task/Thread/*.cpp)
SRCS += $(wildcard $(SRC_DIR)/EWLIB/Task/Process/*cpp)

SRCS += $(wildcard $(SRC_DIR)/EWLIB/Time/Delay/*cpp)
SRCS += $(wildcard $(SRC_DIR)/EWLIB/Time/Time/*cpp)
SRCS += $(wildcard $(SRC_DIR)/EWLIB/Time/Timer/*cpp)

# Main
SRCS += $(wildcard $(SRC_DIR)/*.cpp)

# Build
OBJS = ${SRCS:.cpp=.o}
DEPS = $(OBJS:.o=.d)

OBJECTS = $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(SRCS))

all: main
#$(OBJ_DIR)/%.o : $(SRCS)
#	mkdir -p $(shell dirname $@) 
#	$(CC) $(CXXFLAGS) $(INCLUDE) -c $< -o $@
$(OBJ_DIR)/%.o : %.cpp
	mkdir -p $(shell dirname $@)
	$(CC) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

$(TARGET) : $(OBJECTS)
	$(CC) $(CXXFLAGS) $(INCLUDE) $(OBJECTS) -o  $(TARGET) $(LDFLAGS) $(LIBS) 

.PHONY: clean all
clean:
	rm -f $(OBJECTS) $(TARGET)

-include $(DEPS)
