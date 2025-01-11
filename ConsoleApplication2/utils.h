#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <thread>
#include <conio.h>  // For _kbhit() and _getch() on Windows
#include <sstream>
#include <functional>

#ifdef _WIN32
#include <windows.h>
#elif __linux__
#include <X11/Xlib.h>
#elif __APPLE__
#include <ApplicationServices/ApplicationServices.h>
#endif

const std::string RESET = "\033[0m";

struct ColoredChar {
    char ch;
    std::string color;

    ColoredChar(char c = ' ', const std::string& col = RESET) : ch(c), color(col) {}
};

struct Vec3 {
    float x, y, z;
};

std::string rgbToAnsi(int r, int g, int b);