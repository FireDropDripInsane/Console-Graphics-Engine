#include "CGE.h"

GraphicsEngine graphics;

const int DisplayWIDTH = graphics.WIDTH;
const int DisplayHEIGHT = graphics.HEIGHT;

// Function to handle user input
void handleInput(Camera& camera) {
    if (_kbhit()) {
        char key = _getch();
        switch (key) {
        case 'w':
            camera.moveForward(2.0f);
            break;
        case 's':
            camera.moveForward(-2.0f);
            break;
        case 'a':
            camera.strafe(-1.0f);
            break;
        case 'd':
            camera.strafe(1.0f);
            break;
        case 'q':
            camera.yaw(-0.1f);
            break;
        case 'e':
            camera.yaw(0.1f);
            break;
        case 'r':
            camera.pitch(-0.1f);
            break;
        case 'f':
            camera.pitch(0.1f);
            break;
        default:
            break;
        }
    }
}

// Update your main loop to integrate the GUI
int main() {
    Camera camera({ 0, 0, -100 }, 0, 0, 5.0f);

    Scene Scene1;
    Scene1.InitScene();


    std::string color1 = rgbToAnsi(255, 0, 255);
    std::string color2 = rgbToAnsi(0, 255, 196);
    std::string dcolor1 = rgbToAnsi(255, 255, 255);
    std::string dcolor2 = rgbToAnsi(120, 90, 76);
    std::string ocolor1 = rgbToAnsi(255, 0, 255);
    std::string ocolor2 = rgbToAnsi(0, 255, 196);

    bool isButtonPressed = false;

    GUI::Button ChangeColor(5, 5, 20, 3, "Change Color", rgbToAnsi(0, 255, 0), [&color1, &color2, dcolor1, dcolor2]() {
        color1 = dcolor1;
        color2 = dcolor2;
        });

    GUI::Button ResetColor(5, 10, 20, 3, "Reset Color", rgbToAnsi(255, 0, 0), [&color1, &color2, ocolor1, ocolor2]() {
        color1 = ocolor1;
        color2 = ocolor2;
        });

    GUI::Button DrawCube(5, 15, 20, 3, "DRAW CUBE!!", rgbToAnsi(0, 0, 255), [&isButtonPressed]() {isButtonPressed = true;});

    while (true) {

        auto [xDisplay, yDisplay] = graphics.getMouseCoordinates();
        std::string e{ "X: " + std::to_string(xDisplay / 10) + " Y: " + std::to_string(yDisplay / 24) };
        GUI::Label mousePosLabel(30, 5, e, rgbToAnsi(255, 255, 0));

        GUI::Window window(1, 1, 50, 45, "My Window", rgbToAnsi(0, 255, 0));

        window.addButton(ChangeColor);
        window.addButton(ResetColor);
        window.addButton(DrawCube);
        window.addLabel(mousePosLabel);

        graphics.clearBuffer(*Scene1.nextBuffer, ' ');

        // Draw 3D objects
        graphics.drawCube3D(*Scene1.nextBuffer, camera, { 0, 0, 100 }, 50, '0', color1);
        graphics.drawCube3D(*Scene1.nextBuffer, camera, { 100, 0, 100 }, 50, '#', color2);

        if (isButtonPressed == true)
        {
            graphics.drawCube3D(*Scene1.nextBuffer, camera, { -100, 0, 100 }, 50, '#', rgbToAnsi(255,0,0));
        }

        // Draw GUI elements
        window.draw(*Scene1.nextBuffer);
        ChangeColor.draw(*Scene1.nextBuffer);
        ResetColor.draw(*Scene1.nextBuffer);
        mousePosLabel.draw(*Scene1.nextBuffer);

        graphics.drawScreen(*Scene1.nextBuffer);
        graphics.swapBuffers(Scene1);

        handleInput(camera);

        // Get the current mouse coordinates
        auto [mouseX, mouseY] = graphics.getMouseCoordinates();

        // Simulate mouse click events (you can add further logic here to check if a GUI element is clicked based on mouseX, mouseY)
        if (_kbhit()) {
            char key = _getch();
            if (key == 'c') { // Simulate a click on button1
                if (ChangeColor.isClicked(mouseX / 10, mouseY / 24)) {
                    ChangeColor.onClick();
                }
            }
            if (key == 'c') { // Simulate a click on button2
                if (ResetColor.isClicked(mouseX / 10, mouseY / 24)) {
                    ResetColor.onClick();
                }
            }
            if (key == 'c') { // Simulate a click on button2
                if (DrawCube.isClicked(mouseX / 10, mouseY / 24)) {
                    DrawCube.onClick();
                }
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(graphics.FRAME_DELAY_MS));

    }

    return 0;
}
