cmake_minimum_required(VERSION 3.10)
project(BoardGames)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files
set(SOURCES
    BoardGame_Classes.h
    XO_Classes.cpp
    XO_Classes.h
    XO_Demo.cpp
    TTT4x4_Classes.cpp
    TTT4x4_Classes.h
    TTT4x4_main.cpp
    PYRAMID_TTT_Classes.cpp
    PYRAMID_TTT_Classes.h
    PYRAMID_TTT_main.cpp
    TTT5x5.cpp
    TTT5x5.h
    FourInARow_Classes.cpp
    FourInARow_Classes.h
    FourInARow_main.cpp
    Misere_TTT_Classes.cpp
    Misere_TTT_Classes.h
    Misere_TTT_main.cpp
    Diamond_TTT_Classes.cpp
    Diamond_TTT_Classes.h
    Diamond_TTT_main.cpp
    Word_TTT_Classes.cpp
    Word_TTT_Classes.h
    Word_TTT_main.cpp
    SUS_Classes.cpp
    SUS_Classes.h
    SUS_main.cpp
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES}  "Numerical_Classes.h" "Numerical_Classes.cpp" "Numerical_main.cpp" "Obstacles_Classes.h" "Obstacles_Classes.cpp" "Obstacles_main.cpp" "Infinity_Classes.h" " Infinity_Classes.cpp")

# Compiler-specific options
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
endif()

