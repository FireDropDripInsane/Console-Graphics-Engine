#Console Graphics Engine (CGE) API Documentation

Overview
The Console Graphics Engine (CGE) API provides a framework for creating and rendering simple graphics using a console-based interface. It supports basic shapes like points and triangles and allows for the creation of windows where these shapes can be drawn.

Namespaces
CGE
Contains all the classes and functions for the Graphics Engine.

Classes
CGE::GraphicsEngine
Description
The main class responsible for managing the graphics engine, including creating windows and drawing shapes.

Methods
static Window createWindow(int width, int height)

Description: Creates a new window with the specified width and height.
Parameters:
int width: The width of the window.
int height: The height of the window.
Returns: A Window object.
static GraphicsEngine createGraphicsEngine()

Description: Initializes and returns a new GraphicsEngine object.
Returns: A GraphicsEngine object.
void draw(Window& window, const std::vector<Drawable*>& drawables)

Description: Draws the specified drawables in the provided window.
Parameters:
Window& window: The window where the drawables will be rendered.
const std::vector<Drawable*>& drawables: A vector of pointers to Drawable objects.
void drawLine(std::vector<int>& arr, int x1, int y1, int x2, int y2)

Description: Draws a line between two points and stores the coordinates in the provided vector.
Parameters:
std::vector<int>& arr: A vector to store the coordinates of the line.
int x1: The x-coordinate of the first point.
int y1: The y-coordinate of the first point.
int x2: The x-coordinate of the second point.
int y2: The y-coordinate of the second point.
CGE::GraphicsEngine::Window
Description
Represents a window where graphics can be drawn.

Members
int windowWidth
Description: The width of the window.
int windowHeight
Description: The height of the window.
int CurrentX
Description: The current x-coordinate being processed in the window.
int CurrentY
Description: The current y-coordinate being processed in the window.
CGE::Drawable
Description
An abstract base class for all drawable objects.

Methods
virtual void draw(GraphicsEngine& ge, GraphicsEngine::Window& window) = 0
Description: Pure virtual function that must be implemented by derived classes to define how the object should be drawn.
Parameters:
GraphicsEngine& ge: The graphics engine.
GraphicsEngine::Window& window: The window where the object will be drawn.
CGE::Point
Description
Represents a point that can be drawn in the window.

Constructors
Point(int x, int y)
Description: Initializes a new Point with the specified coordinates.
Parameters:
int x: The x-coordinate of the point.
int y: The y-coordinate of the point.
Methods
void draw(GraphicsEngine& ge, GraphicsEngine::Window& window) override
Description: Draws the point in the specified window.
Parameters:
GraphicsEngine& ge: The graphics engine.
GraphicsEngine::Window& window: The window where the point will be drawn.
CGE::Triangle
Description
Represents a triangle that can be drawn in the window.

Constructors
Triangle(int x1, int y1, int x2, int y2, int x3, int y3)
Description: Initializes a new Triangle with the specified vertices.
Parameters:
int x1: The x-coordinate of the first vertex.
int y1: The y-coordinate of the first vertex.
int x2: The x-coordinate of the second vertex.
int y2: The y-coordinate of the second vertex.
int x3: The x-coordinate of the third vertex.
int y3: The y-coordinate of the third vertex.
Methods
void draw(GraphicsEngine& ge, GraphicsEngine::Window& window) override
Description: Draws the triangle in the specified window.
Parameters:
GraphicsEngine& ge: The graphics engine.
GraphicsEngine::Window& window: The window where the triangle will be drawn.
Functions
std::vector<Drawable*> CGE::createDrawables(const int* data, int length, DrawDataType type)
Description
Creates a vector of Drawable objects based on the provided data and type.

Parameters
const int* data: An array of integers representing the drawing data.
int length: The length of the data array.
DrawDataType type: The type of drawable objects to create (e.g., Point, Triangle).
Returns
A vector of pointers to Drawable objects.
