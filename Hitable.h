//
// Created by 易子沐 on 2019/3/16.
//

#ifndef SIMPLERAYTRACER_HITABLE_H
#define SIMPLERAYTRACER_HITABLE_H

#include "Ray.h"

class Material;

struct HitRecord {
    float parameter;
    Vector3 position;
    Vector3 normal;
    Material* materialPointer;
};

class Hitable {
public:
    virtual bool hit(const Ray& ray, float paramMin, float paramMax, HitRecord& record) const = 0;
};

#endif //SIMPLERAYTRACER_HITABLE_H
