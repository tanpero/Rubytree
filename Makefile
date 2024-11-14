CXX = g++

CXXFLAGS = -Isrc -Wall -Wextra -O2

LDFLAGS = -lstdc++

TARGET = rbt

SRC = test/main.cc
OBJ = $(SRC:.cc=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $^

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJ)

.PHONY: all clean
