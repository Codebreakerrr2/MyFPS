#pragma once

// -------- Vec2 --------
struct Vec2 {
    float x, y;
    Vec2(float v = 0.0f) : x(v), y(v) {}
    Vec2(float x, float y) : x(x), y(y) {}
};

Vec2 operator+(const Vec2& a, const Vec2& b);
Vec2 operator-(const Vec2& a, const Vec2& b);
Vec2 operator*(const Vec2& v, float s);
float Dot(const Vec2& a, const Vec2& b);
float Length(const Vec2& v);
Vec2 Normalize(const Vec2& v);

// -------- Vec3 --------
struct Vec3 {
    float x, y, z;
    Vec3(float v = 0.0f) : x(v), y(v), z(v) {}
    Vec3(float x, float y, float z) : x(x), y(y), z(z) {}
};

Vec3 operator+(const Vec3& a, const Vec3& b);
Vec3 operator-(const Vec3& a, const Vec3& b);
Vec3 operator*(const Vec3& v, float s);
float Dot(const Vec3& a, const Vec3& b);
Vec3 Cross(const Vec3& a, const Vec3& b);
float Length(const Vec3& v);
Vec3 Normalize(const Vec3& v);

// -------- Vec4 --------
struct Vec4 {
    float x, y, z, w;
    Vec4(float v = 0.0f) : x(v), y(v), z(v), w(v) {}
    Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
};

Vec4 operator+(const Vec4& a, const Vec4& b);
Vec4 operator-(const Vec4& a, const Vec4& b);
Vec4 operator*(const Vec4& v, float s);
float Dot(const Vec4& a, const Vec4& b);
float Length(const Vec4& v);
Vec4 Normalize(const Vec4& v);
