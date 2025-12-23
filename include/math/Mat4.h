#pragma once
#include <cmath>
#include "Math/Vec.h"


namespace Math {

    // 4x4 Matrix (column-major wie OpenGL)
    struct Mat4 {
        float m[16];

        // -------- Konstruktoren --------
        Mat4();                     // Identität
        explicit Mat4(float diag);  // Diagonale setzen

        // -------- Factory Funktionen --------
        static Mat4 Identity();
        static Mat4 Translation(const Vec3& t);
        static Mat4 Scale(const Vec3& s);
        static Mat4 RotationX(float radians);
        static Mat4 RotationY(float radians);
        static Mat4 RotationZ(float radians);

        static Mat4 Perspective(
            float fovRadians,
            float aspect,
            float nearPlane,
            float farPlane
        );

        static Mat4 LookAt(
            const Vec3& eye,
            const Vec3& center,
            const Vec3& up
        );

    };

    // -------- Operatoren --------
    Mat4 operator*(const Mat4& a, const Mat4& b);
    Vec4 operator*(const Mat4& m, const Vec4& v);

}