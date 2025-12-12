@echo off
echo Building Board Games Collection...
g++ -std=c++17 ^
    XO_Classes.cpp ^
    XO_Demo.cpp ^
    TTT4x4_Classes.cpp ^
    TTT4x4_main.cpp ^
    PYRAMID_TTT_Classes.cpp ^
    PYRAMID_TTT_main.cpp ^
    TTT5x5.cpp ^
    FourInARow_Classes.cpp ^
    FourInARow_main.cpp ^
    Misere_TTT_Classes.cpp ^
    Misere_TTT_main.cpp ^
    Diamond_TTT_Classes.cpp ^
    Diamond_TTT_main.cpp ^
    Word_TTT_Classes.cpp ^
    Word_TTT_main.cpp ^
    SUS_Classes.cpp ^
    SUS_main.cpp ^
    -o BoardGames.exe

if %ERRORLEVEL% EQU 0 (
    echo Build successful! Run BoardGames.exe to play.
) else (
    echo Build failed! Check errors above.
    pause
)

