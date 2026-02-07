CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
LDFLAGS = -lSDL2

TARGET = tetris
SOURCES = main.cpp game.cpp pieces.cpp

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)