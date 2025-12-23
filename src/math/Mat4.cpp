#include "math/Mat4.h"
namespace Math {
    Mat4::Mat4() {
        for (int i = 0; i < 16; i++) m[i]=0.0f;
        m[0]=m[5]=m[10]=m[15]= 1.0f;
    }

    Mat4::Mat4(float diag) {
        for (int i = 0; i < 16; i++) m[i]=0.0f;
        m[0]=m[5]=m[10]=m[15]= diag;
    }

    Mat4 Mat4::Identity() {
        return Mat4(1.0f);
    }

    Mat4 Mat4::Translation(const Vec3 &t) {
        Mat4 r(1.0f);
        r.m[12]=t.x;
        r.m[13]=t.y;
        r.m[14]=t.z;
    }

    Mat4 Mat4::Scale(const Vec3 &s) {
        Mat4 r(1.0f);
        r.m[0]  = s.x;
        r.m[5]  = s.y;
        r.m[10] = s.z;
        return r;
    }

    Mat4 Mat4::RotationX(float radians) {
        Mat4 r(1.0f);
        float s= std::sin(radians);
        float c= std::cos(radians);
        r.m[0]  = c;
        r.m[2]  = -s;
        r.m[8]  = s;
        r.m[10] = c;
        return r;
    }


    Mat4 Mat4::RotationY(float radians) {
        Mat4 r(1.0f);
        float c = std::cos(radians);
        float s = std::sin(radians);
        r.m[0]  = c;
        r.m[2]  = -s;
        r.m[8]  = s;
        r.m[10] = c;
        return r;
    }

    Mat4 Mat4::RotationZ(float radians) {
        Mat4 r(1.0f);
        float c = std::cos(radians);
        float s = std::sin(radians);
        r.m[0] = c;
        r.m[1] = s;
        r.m[4] = -s;
        r.m[5] = c;
        return r;
    }

    Mat4 Mat4::Perspective(float fovRadians, float aspect, float nearPlane, float farPlane) {
        Mat4 result(0.0f);

        float f = 1.0f / tan(fovRadians / 2.0f);

        result.m[0] = f / aspect;
        result.m[5] = f;
        result.m[10] = -(farPlane + nearPlane) / (farPlane - nearPlane);
        result.m[11] = -1.0f;
        result.m[14] = -(2.0f * farPlane * nearPlane) / (farPlane - nearPlane);

        return result;
    }


    Mat4 Mat4::LookAt(const Vec3& eye, const Vec3& center, const Vec3& up)
    {
        Vec3 f = Normalize(center - eye);
        Vec3 r = Normalize(Cross(f, up));
        Vec3 u = Cross(r, f);

        Mat4 m(1.0f);

        m.m[0] =  r.x;
        m.m[1] =  u.x;
        m.m[2] = -f.x;

        m.m[4] =  r.y;
        m.m[5] =  u.y;
        m.m[6] = -f.y;

        m.m[8]  =  r.z;
        m.m[9]  =  u.z;
        m.m[10] = -f.z;

        m.m[12] = -Dot(r, eye);
        m.m[13] = -Dot(u, eye);
        m.m[14] =  Dot(f, eye);

        return m;
    }


    // ---------------- Operators ----------------

    Mat4 operator*(const Mat4& a, const Mat4& b) {
        Mat4 result(0.0f);
        // column-major multiplication: result = a * b
        for (int col = 0; col < 4; ++col) {
            for (int row = 0; row < 4; ++row) {
                float sum = 0.0f;
                for (int k = 0; k < 4; ++k) {
                    sum += a.m[k * 4 + row] * b.m[col * 4 + k];
                }
                result.m[col * 4 + row] = sum;
            }
        }
        return result;
    }

    Vec4 operator*(const Mat4& m, const Vec4& v) {
        // column-major: multiply matrix by column vector
        return Vec4(
            m.m[0]  * v.x + m.m[4]  * v.y + m.m[8]  * v.z + m.m[12] * v.w,
            m.m[1]  * v.x + m.m[5]  * v.y + m.m[9]  * v.z + m.m[13] * v.w,
            m.m[2]  * v.x + m.m[6]  * v.y + m.m[10] * v.z + m.m[14] * v.w,
            m.m[3]  * v.x + m.m[7]  * v.y + m.m[11] * v.z + m.m[15] * v.w
        );
    }
}
