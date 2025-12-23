#include <cmath>
#include "math/Vec.h"
namespace Math {
    // ===================== Vec2 =====================
    Vec2 operator+(const Vec2 &a, const Vec2 &b) {
        return Vec2(a.x + b.x, a.y + b.y);
    }

    Vec2 operator-(const Vec2 &a, const Vec2 &b) {
        return Vec2(a.x - b.x, a.y - b.y);
    }

    Vec2 operator*(const Vec2 &v, float s) {
        return Vec2(v.x * s, v.y * s);
    }

    float Dot(const Vec2 &a, const Vec2 &b) {
        return a.x * b.x + a.y * b.y;
    }

    float Length(const Vec2 &v) {
        return std::sqrt(v.x * v.x + v.y * v.y);
    }

    Vec2 Normalize(const Vec2 &v) {
        float len = Math::Length(v);
        if (len == 0.0f) return Vec2(0.0f);
        return Vec2(v.x / len, v.y / len);
    }

    // ===================== Vec3 =====================
    Vec3 operator+(const Vec3 &a, const Vec3 &b) {
        return Vec3(a.x + b.x, a.y + b.y, a.z + b.z);
    }

    Vec3 operator-(const Vec3 &a, const Vec3 &b) {
        return Vec3(a.x - b.x, a.y - b.y, a.z - b.z);
    }

    Vec3 operator*(const Vec3 &v, float s) {
        return Vec3(v.x * s, v.y * s, v.z * s);
    }

    float Dot(const Vec3 &a, const Vec3 &b) {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    Vec3 Cross(const Vec3 &a, const Vec3 &b) {
        return Vec3(
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x
        );
    }

    float Length(const Vec3 &v) {
        return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    }

    Vec3 Normalize(const Vec3 &v) {
        float len = Math::Length(v);
        if (len == 0.0f) return Vec3(0.0f);
        return Vec3(v.x / len, v.y / len, v.z / len);
    }

    // ===================== Vec4 =====================
    Vec4 operator+(const Vec4 &a, const Vec4 &b) {
        return Vec4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
    }

    Vec4 operator-(const Vec4 &a, const Vec4 &b) {
        return Vec4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
    }

    Vec4 operator*(const Vec4 &v, float s) {
        return Vec4(v.x * s, v.y * s, v.z * s, v.w * s);
    }

    float Dot(const Vec4 &a, const Vec4 &b) {
        return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
    }

    float Length(const Vec4 &v) {
        return std::sqrt(
            v.x * v.x +
            v.y * v.y +
            v.z * v.z +
            v.w * v.w
        );
    }

    Vec4 Normalize(const Vec4 &v) {
        float len = Math::Length(v);
        if (len == 0.0f) return Vec4(0.0f);
        return Vec4(v.x / len, v.y / len, v.z / len, v.w / len);
    }
}