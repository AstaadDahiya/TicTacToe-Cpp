CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
SRC = src/TicTacToe.cpp
TARGET = tictactoe

all: $(TARGET)

$(TARGET): $(SRC)
    $(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
    rm -f $(TARGET)

run: $(TARGET)
    ./$(TARGET)