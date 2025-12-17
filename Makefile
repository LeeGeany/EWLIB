# C++ 컴파일러
CC = g++
#CC = aarch64-linux-gnu-g++

# C++ 컴파일러 옵션
CXXFLAGS = -g -std=c++17 -pthread

FFTW_PREFIX = /usr/local/fftw-x86

# Library
LIBS += -L$(FFTW_PREFIX)/lib -lfftw3 -lm

# Include 파일 디렉토리
INCLUDE += -I$(SRC_DIR)
INCLUDE += -I$(FFTW_PREFIX)/include

# 링커 옵션
LDFLAGS = -Wl,-rpath,$(FFTW_PREFIX)/lib

# 소스 파일 디렉토리
SRC_DIR = .

# 오브젝트 파일 디렉토리
OBJ_DIR = Objs

# 생성하고자 하는 실행 파일 이름
TARGET = main

# === EWLIB 소스 목록 ===
SRCS_EWLIB += $(wildcard $(SRC_DIR)/EWLIB/Communication/Ethernet/Socket/*.cpp)
SRCS_EWLIB += $(wildcard $(SRC_DIR)/EWLIB/Communication/Ethernet/Client/*.cpp)
SRCS_EWLIB += $(wildcard $(SRC_DIR)/EWLIB/Communication/Ethernet/Server/*.cpp)
SRCS_EWLIB += $(wildcard $(SRC_DIR)/EWLIB/Communication/Event/Epoll/*.cpp)
SRCS_EWLIB += $(wildcard $(SRC_DIR)/EWLIB/Communication/Event/Signal/*.cpp)
SRCS_EWLIB += $(wildcard $(SRC_DIR)/EWLIB/Communication/IPC/MsgQ/*.cpp)

SRCS_EWLIB += $(wildcard $(SRC_DIR)/EWLIB/Container/*cpp)

SRCS_EWLIB += $(wildcard $(SRC_DIR)/EWLIB/FileIO/Dir/*cpp)
SRCS_EWLIB += $(wildcard $(SRC_DIR)/EWLIB/FileIO/File/*cpp)
SRCS_EWLIB += $(wildcard $(SRC_DIR)/EWLIB/FileIO/FIO/*cpp)

SRCS_EWLIB += $(wildcard $(SRC_DIR)/EWLIB/Sync/Lock/*.cpp)
SRCS_EWLIB += $(wildcard $(SRC_DIR)/EWLIB/Sync/Mutex/*.cpp)
SRCS_EWLIB += $(wildcard $(SRC_DIR)/EWLIB/Sync/Spinlock/*.cpp)
SRCS_EWLIB += $(wildcard $(SRC_DIR)/EWLIB/Sync/Waiter/*.cpp)

SRCS_EWLIB += $(wildcard $(SRC_DIR)/EWLIB/Task/Thread/*.cpp)
SRCS_EWLIB += $(wildcard $(SRC_DIR)/EWLIB/Task/Process/*cpp)

SRCS_EWLIB += $(wildcard $(SRC_DIR)/EWLIB/Time/Delay/*cpp)
SRCS_EWLIB += $(wildcard $(SRC_DIR)/EWLIB/Time/Time/*cpp)
SRCS_EWLIB += $(wildcard $(SRC_DIR)/EWLIB/Time/Timer/*cpp)

# Main 소스
SRCS_EWLIB = $(wildcard $(SRC_DIR)/*.cpp)

# 전체 소스
SRCS = $(SRCS_EWLIB) $(SRCS_MAIN)

# 오브젝트 파일 매핑
OBJECTS = $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(SRCS))
OBJECTS_EWLIB = $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(SRCS_EWLIB))

# 정적 라이브러리 이름
STATIC_LIB = lib/libewlib.a

# 의존성 파일
DEPS = $(OBJECTS:.o=.d)

# === 빌드 규칙 ===

all: $(STATIC_LIB) $(TARGET)

.PHONY: lib
lib: $(STATIC_LIB)

# 정적 라이브러리 생성
$(STATIC_LIB): $(OBJECTS_EWLIB)
	mkdir -p lib
	ar rcs $@ $^

# main 빌드: 라이브러리와 링크
$(TARGET): $(OBJECTS_MAIN) $(STATIC_LIB)
	$(CC) $(CXXFLAGS) $(INCLUDE) $(OBJECTS_MAIN) -Llib -lewlib -o $(TARGET) $(LDFLAGS) $(LIBS)

# 모든 객체 생성 규칙
$(OBJ_DIR)/%.o: %.cpp
	mkdir -p $(shell dirname $@)
	$(CC) $(CXXFLAGS) $(INCLUDE) -MMD -MP -c $< -o $@

.PHONY: clean all
clean:
	rm -rf $(OBJ_DIR) lib $(TARGET)

# 자동 의존성 로드
-include $(DEPS)
