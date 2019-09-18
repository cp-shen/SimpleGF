#ifndef CAMERA_H
#define CAMERA_H

#include "../math/MathCommom.h"
#include "../utils/Window.h"

namespace SimpleGF {

class Camera {
    public:
        Camera();
        virtual ~Camera();

        Matrix projectionMatrix() const;
        Matrix viewMatrix() const;
        void setAspectByWindow(const Window& window);

        float fov; // field of view, in radians
        float aspect; // width / height;
        float near;
        float far;

        Vector3 position;
        Quaternion rotation;
};

}

#endif /* CAMERA_H */
