//
// Created by 易子沐 on 2019/3/15.
//

#ifndef SIMPLERAYTRACER_VECTOR3_H
#define SIMPLERAYTRACER_VECTOR3_H

#include <iostream>
#include <stdlib.h>
#include <math.h>

class Vector3 {
public:
    float e[3];

    Vector3() {}
    Vector3(float e0, float e1, float e2) {
        e[0] = e0;
        e[1] = e1;
        e[2] = e2;
    }
    inline float x() const { return e[0]; }
    inline float y() const { return e[1]; }
    inline float z() const { return e[2]; }
    inline float r() const { return e[0]; }
    inline float g() const { return e[1]; }
    inline float b() const { return e[2]; }

    inline const Vector3& operator+() const { return *this; }
    inline Vector3 operator-() const { return Vector3(-e[0], -e[1], -e[2]); }
    inline float operator[](int index) const { return e[index]; }
    inline float& operator[](int index) { return e[index]; }

    inline Vector3& operator+=(const Vector3 &v2);
    inline Vector3& operator-=(const Vector3 &v2);
    inline Vector3& operator*=(const Vector3 &v2);
    inline Vector3& operator/=(const Vector3 &v2);
    inline Vector3& operator*=(const float t);
    inline Vector3& operator/=(const float t);

    inline float length() const { return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]); }
    inline float squaredLength() const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }
    inline void makeUnitVector();
};

inline std::istream& operator>>(std::istream &is, Vector3 &vector3) {
    is >> vector3.e[0] >> vector3.e[1] >> vector3.e[2];
    return is;
}

inline std::ostream& operator<<(std::ostream &os, const Vector3 &vector3) {
    os << vector3.e[0] << " " << vector3.e[1] << " " << vector3.e[2];
    return os;
}

inline void Vector3::makeUnitVector() {
    float k = 1.0 / sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
    e[0] *= k;
    e[1] *= k;
    e[2] *= k;
}

inline Vector3 operator+(const Vector3 &v1, const Vector3 &v2) {
    return Vector3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}

inline Vector3 operator-(const Vector3 &v1, const Vector3 &v2) {
    return Vector3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}

inline Vector3 operator*(const Vector3 &v1, const Vector3 &v2) {
    return Vector3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}

inline Vector3 operator/(const Vector3 &v1, const Vector3 &v2) {
    return Vector3(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
}

inline Vector3 operator*(float k, const Vector3 &vector3) {
    return Vector3(k * vector3.e[0], k * vector3.e[1], k * vector3.e[2]);
}

inline Vector3 operator/(Vector3 vector3, float k) {
    return Vector3(vector3.e[0] / k, vector3.e[1] / k, vector3.e[2] / k);
}

inline Vector3 operator*(const Vector3 &vector3, float k) {
    return Vector3(vector3.e[0] * k, vector3.e[1] * k, vector3.e[2] * k);
}

inline float dot(const Vector3 &v1, const Vector3 &v2) {
    return v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v2.e[2];
}

inline Vector3 cross(const Vector3 &v1, const Vector3 &v2) {
    return Vector3((v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1]),
                   (-(v1.e[0] * v2.e[2] - v1.e[2] * v2.e[0])),
                   (v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]));
}

inline Vector3& Vector3::operator+=(const Vector3 &v2) {
    e[0] += v2.e[0];
    e[1] += v2.e[1];
    e[2] += v2.e[2];
    return *this;
}

inline Vector3& Vector3::operator-=(const Vector3 &v2) {
    e[0] -= v2.e[0];
    e[1] -= v2.e[1];
    e[2] -= v2.e[2];
    return *this;
}

inline Vector3& Vector3::operator*=(const Vector3 &v2) {
    e[0] *= v2.e[0];
    e[1] *= v2.e[1];
    e[2] *= v2.e[2];
    return *this;
}

inline Vector3& Vector3::operator/=(const Vector3 &v2) {
    e[0] /= v2.e[0];
    e[1] /= v2.e[1];
    e[2] /= v2.e[2];
    return *this;
}

inline Vector3& Vector3::operator*=(const float t) {
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
}

inline Vector3& Vector3::operator/=(const float t) {
    float k = 1.0 / t;

    e[0] *= k;
    e[1] *= k;
    e[2] *= k;
    return *this;
}

inline Vector3 unitVector(Vector3 vector3) {
    return vector3 / vector3.length();
}

#endif //SIMPLERAYTRACER_VECTOR3_H
