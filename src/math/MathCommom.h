#ifndef MATH_COMMON_H
#define MATH_COMMON_H

#include "../thirdparty/raymath.h"

namespace SimpleGF {

inline Matrix operator*(const Matrix& left, const Matrix& right) {
    return MatrixMultiply(right, left);
}

struct Transform {
    public:
        Vector3 scale;
        Quaternion rotation;
        Vector3 translation;

        Transform() {
            rotation = QuaternionIdentity();
            scale = Vector3One();
            translation = Vector3Zero();
        }

        Matrix toMatrix() {
            Matrix mScale = MatrixScale(scale.x, scale.y, scale.z);
            Matrix mRotate = QuaternionToMatrix(rotation);
            Matrix mTranslate = MatrixTranslate(translation.x, translation.y, translation.z);

            Matrix result = mTranslate * mRotate * mScale;
            return result;
        }
};

} // namespace SimpleGF

#endif // MATH_COMMON_H
