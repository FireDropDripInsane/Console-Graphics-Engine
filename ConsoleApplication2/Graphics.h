#pragma once
#include "utils.h"  // Make sure this contains Vec3 and ColoredChar
#include <vector>
#include <string>
#include <utility>  // For std::pai
#include "Scene.h"

// Forward declare Camera class to avoid circular dependency
class Camera;

class GraphicsEngine {
public:
    static const int HEIGHT = 50;  // Screen height
    static const int WIDTH = 200;  // Screen width
    const int FRAME_DELAY_MS = 50; // Frame delay in milliseconds

    // Function declarations
    std::pair<int, int> getMouseCoordinates();  // Function for mouse coordinates
    std::pair<int, int> projectTo2D(const Vec3& point);  // Function to project 3D point to 2D screen

    void clearBuffer(std::vector<std::vector<ColoredChar>>& buffer, char ch = ' ', const std::string& color = RESET);
    void drawScreen(const std::vector<std::vector<ColoredChar>>& buffer);
    void drawPixel(std::vector<std::vector<ColoredChar>>& buffer, int x, int y, char ch = ' ', const std::string& color = RESET);
    void drawLine(std::vector<std::vector<ColoredChar>>& buffer, int x0, int y0, int x1, int y1, char ch = '-', const std::string& color = RESET);
    void drawLine3D(std::vector<std::vector<ColoredChar>>& buffer, const Camera& camera, const Vec3& p0, const Vec3& p1, char ch = '-', const std::string& color = RESET);
    void drawCube3D(std::vector<std::vector<ColoredChar>>& buffer, const Camera& camera, const Vec3& center, float size, char ch = '#', const std::string& color = RESET);
    void swapBuffers(Scene& scene);
};
