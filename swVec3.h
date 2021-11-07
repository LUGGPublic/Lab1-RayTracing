#pragma once
#define _USE_MATH_DEFINES
#include <cfloat>
#include <cmath>

class swVec3 {
  public:
    swVec3() = default;
    swVec3(float m0, float m1, float m2) : m{m0, m1, m2} {}

    float x() const { return m[0]; }
    float y() const { return m[1]; }
    float z() const { return m[2]; }

    float operator[](int i) const { return m[i]; }

    swVec3 operator*(int a) const {
        return swVec3(a * m[0], a * m[1], a * m[2]);
    }
    swVec3 operator*(float a) const {
        return swVec3(a * m[0], a * m[1], a * m[2]);
    }
    friend swVec3 operator*(float a, const swVec3 &v) {
        return swVec3(a * v[0], a * v[1], a * v[2]);
    }
    swVec3 operator+(const swVec3 &v) const {
        return swVec3(m[0] + v[0], m[1] + v[1], m[2] + v[2]);
    }
    swVec3 operator-() const { return swVec3(-m[0], -m[1], -m[2]); }
    swVec3 operator-(const swVec3 &v) const {
        return swVec3(m[0] - v[0], m[1] - v[1], m[2] - v[2]);
    }
    float operator*(const swVec3 &v) const {
        return m[0] * v[0] + m[1] * v[1] + m[2] * v[2];
    }
    swVec3 operator%(const swVec3 &v) const {
        return swVec3(m[1] * v[2] - m[2] * v[1], m[2] * v[0] - m[0] * v[2],
                      m[0] * v[1] - m[1] * v[0]);
    }
    swVec3 &operator+=(const swVec3 &v) {
        m[0] += v[0];
        m[1] += v[1];
        m[2] += v[2];
        return *this;
    }
    swVec3 &operator*=(float a) {
        m[0] *= a;
        m[1] *= a;
        m[2] *= a;
        return *this;
    }
    swVec3 &normalize() {
        float l = 1.0f / std::sqrt(m[0] * m[0] + m[1] * m[1] + m[2] * m[2]);
        m[0] *= l;
        m[1] *= l;
        m[2] *= l;
        return *this;
    }

  public:
    float m[3]{0.0f, 0.0f, 0.0f};
};
using Color = swVec3; // RGB color
