CC := g++
CFLAGS := -Wall -g
TARGET := app


SRC_DIR := .
OBJ_DIR := obj

# $(wildcard *.cpp /xxx/xxx/*.cpp): get all .cpp files from the current directory and dir "/xxx/xxx/"
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
# $(patsubst %.cpp,%.o,$(SRCS)): substitute all ".cpp" file name strings to ".o" file name strings
OBJS := $(patsubst %.cpp,%.o,$(SRCS))

all: $(TARGET)
$(TARGET): $(OBJS)
	$(CC) -o $@ $^
%.o: %.cpp
	$(CC) $(CFLAGS) -c $<
clean:
	rm -rf $(TARGET) *.o *.ppm