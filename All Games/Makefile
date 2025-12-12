# Makefile for Board Games Collection

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic
TARGET = BoardGames
SOURCES = XO_Classes.cpp \
          XO_Demo.cpp \
          TTT4x4_Classes.cpp \
          TTT4x4_main.cpp \
          PYRAMID_TTT_Classes.cpp \
          PYRAMID_TTT_main.cpp \
          TTT5x5.cpp \
          FourInARow_Classes.cpp \
          FourInARow_main.cpp \
          Misere_TTT_Classes.cpp \
          Misere_TTT_main.cpp \
          Diamond_TTT_Classes.cpp \
          Diamond_TTT_main.cpp \
          Word_TTT_Classes.cpp \
          Word_TTT_main.cpp \
          SUS_Classes.cpp \
          SUS_main.cpp

OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean

