#include "Graphics.h"
#include "Camera.h"
#include "Scene.h"

std::pair<int, int> GraphicsEngine::getMouseCoordinates() {
    int x = 0, y = 0;

#ifdef _WIN32
    POINT p;
    if (GetCursorPos(&p)) {
        x = p.x;
        y = p.y;
    }
#elif __linux__
    Display* display = XOpenDisplay(NULL);
    if (display) {
        Window root = DefaultRootWindow(display);
        Window win;
        int tmpX, tmpY;
        unsigned int mask;
        XQueryPointer(display, root, &win, &win, &tmpX, &tmpY, &x, &y, &mask);
        XCloseDisplay(display);
    }
#elif __APPLE__
    CGEventSourceRef source = CGEventSourceCreate(kCGEventSourceStateHIDSystemState);
    CGPoint point = CGEventGetLocation(CGEventCreate(source));
    x = static_cast<int>(point.x);
    y = static_cast<int>(point.y);
    CFRelease(source);
#endif

    return { x, y };
}

std::pair<int, int> GraphicsEngine::projectTo2D(const Vec3& point) {
    float distance = 50.0f;
    float factor = distance / (distance + point.z);

    // Adjust for character aspect ratio (2:1 width:height)
    float aspectRatio = 2.0f;

    int screenX = static_cast<int>(point.x * factor + WIDTH / 2);
    int screenY = static_cast<int>(point.y * factor / aspectRatio + HEIGHT / 2);

    return { screenX, screenY };
}

void GraphicsEngine::clearBuffer(std::vector<std::vector<ColoredChar>>& buffer, char ch, const std::string& color) {
    for (int y = 0; y < HEIGHT; ++y) {
        std::fill(buffer[y].begin(), buffer[y].end(), ColoredChar(ch, color));
    }
}

void GraphicsEngine::drawScreen(const std::vector<std::vector<ColoredChar>>& buffer) {
    std::cout << "\033[H";  // ANSI escape code to move the cursor to the top left corner
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            std::cout << buffer[y][x].color << buffer[y][x].ch;
        }
        std::cout << '\n';
    }
    std::cout << RESET;  // Reset color after drawing
}

void GraphicsEngine::drawPixel(std::vector<std::vector<ColoredChar>>& buffer, int x, int y, char ch, const std::string& color) {
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
        buffer[y][x] = ColoredChar(ch, color);
    }
}

void GraphicsEngine::drawLine(std::vector<std::vector<ColoredChar>>& buffer, int x0, int y0, int x1, int y1, char ch, const std::string& color) {
    int dx = std::abs(x1 - x0);
    int dy = std::abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        drawPixel(buffer, x0, y0, ch, color);

        if (x0 == x1 && y0 == y1) break;
        int e2 = err * 2;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

void GraphicsEngine::drawLine3D(std::vector<std::vector<ColoredChar>>& buffer, const Camera& camera, const Vec3& p0, const Vec3& p1, char ch, const std::string& color) {
    Vec3 transformedP0 = camera.applyTransform(p0);
    Vec3 transformedP1 = camera.applyTransform(p1);

    auto [x0, y0] = projectTo2D(transformedP0);
    auto [x1, y1] = projectTo2D(transformedP1);
    drawLine(buffer, x0, y0, x1, y1, ch, color);
}

void GraphicsEngine::drawCube3D(std::vector<std::vector<ColoredChar>>& buffer, const Camera& camera, const Vec3& center, float size, char ch, const std::string& color) {
    float halfSize = size / 2;

    Vec3 vertices[8] = {
        {center.x - halfSize, center.y - halfSize, center.z - halfSize},
        {center.x + halfSize, center.y - halfSize, center.z - halfSize},
        {center.x + halfSize, center.y + halfSize, center.z - halfSize},
        {center.x - halfSize, center.y + halfSize, center.z - halfSize},
        {center.x - halfSize, center.y - halfSize, center.z + halfSize},
        {center.x + halfSize, center.y - halfSize, center.z + halfSize},
        {center.x + halfSize, center.y + halfSize, center.z + halfSize},
        {center.x - halfSize, center.y + halfSize, center.z + halfSize},
    };

    int edges[12][2] = {
        {0, 1}, {1, 2}, {2, 3}, {3, 0},
        {4, 5}, {5, 6}, {6, 7}, {7, 4},
        {0, 4}, {1, 5}, {2, 6}, {3, 7}
    };

    for (int i = 0; i < 12; ++i) {
        drawLine3D(buffer, camera, vertices[edges[i][0]], vertices[edges[i][1]], ch, color);
    }
}

void GraphicsEngine::swapBuffers(Scene& scene) {
    std::vector<std::vector<ColoredChar>>* temp = scene.currentBuffer;
    scene.currentBuffer = scene.nextBuffer;
    scene.nextBuffer = temp;
}