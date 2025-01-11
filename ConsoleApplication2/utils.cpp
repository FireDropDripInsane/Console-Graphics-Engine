#include "utils.h"

std::string rgbToAnsi(int r, int g, int b) {
    std::ostringstream oss;
    oss << "\033[38;2;" << r << ";" << g << ";" << b << "m";
    return oss.str();
}