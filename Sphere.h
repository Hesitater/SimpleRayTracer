//
// Created by 易子沐 on 2019/3/16.
//

#ifndef SIMPLERAYTRACER_SPHERE_H
#define SIMPLERAYTRACER_SPHERE_H

#include "Hitable.h"

class Sphere: public Hitable {
public:
    Vector3 center;
    float radius;
    Material* material;

    Sphere() {}
    Sphere(Vector3 newCenter, float newRadius, Material *newMaterial) : center(newCenter), radius(newRadius) {
        material = newMaterial;
    };
    virtual bool hit(const Ray& ray, float paramMin, float paramMax, HitRecord& record) const;
};

// Check hit or not. If hit, store information in record
bool Sphere::hit(const Ray &ray, float paramMin, float paramMax, HitRecord &record) const {
    Vector3 co = ray.origin() - this->center;
    float a = dot(ray.direction(), ray.direction());
    float b = dot(ray.direction(), co);
    float c = dot(co, co) - radius * radius;
    float discriminant = b * b - a * c;
    if (discriminant > 0) {
        float param = (-b - sqrt(discriminant)) / a;
        if (param < paramMax && param > paramMin) { // In between range, use current solution(param)
            record.parameter = param;
            record.position = ray.pointAtParameter(param);
            record.normal = (record.position - this->center) / this->radius; // Normalized normal
            record.materialPointer = this->material;
            return true;
        } else { // Out of range, use another solution
            param = (-b + sqrt(discriminant)) / a;
            if (param < paramMax && param > paramMin) {
                record.parameter = param;
                record.position = ray.pointAtParameter(param);
                record.normal = (record.position - this->center) / this->radius; // Normalized normal
                record.materialPointer = this->material;
                return true;
            }
        }
    }
    return false;
}
#endif //SIMPLERAYTRACER_SPHERE_H
