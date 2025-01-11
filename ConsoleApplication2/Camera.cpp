#include "Camera.h"

Vec3 Camera::applyTransform(const Vec3& point) const {
    Vec3 transformed = point;

    // Rotate around Y-axis
    float cosY = std::cos(rotationY);
    float sinY = std::sin(rotationY);
    float x = transformed.x * cosY - transformed.z * sinY;
    float z = transformed.x * sinY + transformed.z * cosY;
    transformed.x = x;
    transformed.z = z;

    // Rotate around X-axis
    float cosX = std::cos(rotationX);
    float sinX = std::sin(rotationX);
    float y = transformed.y * cosX - transformed.z * sinX;
    transformed.z = transformed.y * sinX + transformed.z * cosX;
    transformed.y = y;

    // Translate by camera position
    transformed.x -= position.x;
    transformed.y -= position.y;
    transformed.z -= position.z;

    return transformed;
}


void Camera::moveForward(float delta) {
    position.z += speed * delta;
}

void Camera::strafe(float delta) {
    position.x += speed * delta;
}

void Camera::pitch(float delta) {
    rotationX += delta;
}

void Camera::yaw(float delta) {
    rotationY += delta;
}