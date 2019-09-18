#include "./Camera.h"

using namespace SimpleGF;

Camera::Camera() {
    fov = 45.0f * DEG2RAD;
    aspect = 4.0f / 3.0f;
    near = 0.1f;
    far = 100.0f;

    position = Vector3Zero();
    rotation = QuaternionIdentity();
}

Camera::~Camera() {

}

Matrix Camera::projectionMatrix() const {
    return MatrixPerspective(fov, aspect, near, far);
}

Matrix Camera::viewMatrix() const {
    Vector3 forwardDir = Vector3Zero();
    forwardDir.z = 1;
    forwardDir = Vector3RotateByQuaternion(forwardDir, rotation);

    Vector3 target = Vector3Add(position, forwardDir);

    Vector3 upDir = Vector3Zero();
    upDir.y = 1;
    forwardDir = Vector3RotateByQuaternion(upDir, rotation);

    return MatrixLookAt(position, target, upDir);
}

void Camera::setAspectByWindow(const Window& window) {
    aspect = (GLfloat) window.width() / (GLfloat) window.height();
}

