//
// Created by 易子沐 on 2019/3/15.
//

#ifndef SIMPLERAYTRACER_RAY_H
#define SIMPLERAYTRACER_RAY_H

#include "Vector3.h"

class Ray {
public:
    Vector3 A;
    Vector3 B;

    Ray() {}
    Ray(const Vector3& origin, const Vector3& direction) {
        A = origin;
        B = direction;
    }
    Vector3 origin() const { return A; }
    Vector3 direction() const { return B; }
    Vector3 pointAtParameter(float k) const { return A + k * B; }
};

#endif //SIMPLERAYTRACER_RAY_H
