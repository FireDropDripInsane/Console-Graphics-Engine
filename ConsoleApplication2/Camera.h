#pragma once
#include "utils.h"  // Include this to ensure Vec3 is defined

class Camera {
public:
    Vec3 position;       // Position of the camera
    float rotationX;     // Rotation around X-axis
    float rotationY;     // Rotation around Y-axis
    float speed;         // Movement speed

    // Constructor with default values
    Camera(const Vec3& pos = { 0, 0, 0 }, float rotX = 0, float rotY = 0, float spd = 5.0f)
        : position(pos), rotationX(rotX), rotationY(rotY), speed(spd) {}

    // Function declarations
    Vec3 applyTransform(const Vec3& point) const;
    void moveForward(float delta);
    void strafe(float delta);
    void pitch(float delta);
    void yaw(float delta);
};
