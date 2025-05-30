CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -I.

SRCS := encoder.cpp decoder.cpp tests.cpp
OBJS := $(SRCS:.cpp=.o)
TARGET := shannon_coding_test

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all test clean