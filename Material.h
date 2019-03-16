//
// Created by 易子沐 on 2019/3/16.
//

#ifndef SIMPLERAYTRACER_MATERIAL_H
#define SIMPLERAYTRACER_MATERIAL_H

#include "Hitable.h"

class Material {
public:
    virtual bool scatter(const Ray& incidentRay, const HitRecord& hitRecord, Vector3& attenuation, Ray& scatteredRay) const = 0;
};

Vector3 randomInUnitSphere() {
    Vector3 p;
    do {
        p = 2.0 * Vector3(drand48(), drand48(), drand48()) - Vector3(1, 1, 1);
    } while (p.squaredLength() >= 1.0);
    return p;
}

class Lambertian : public Material {
public:
    Vector3 albedo;

    Lambertian(const Vector3 &newAlbedo) : albedo(newAlbedo) {}
    virtual bool scatter(const Ray &incidentRay, const HitRecord &hitRecord, Vector3 &attenuation,
                 Ray &scatteredRay) const {
        Vector3 target = hitRecord.position + hitRecord.normal + randomInUnitSphere();
        scatteredRay = Ray(hitRecord.position, target - hitRecord.position);
        attenuation = this->albedo;
        return true;
    }
};

Vector3 reflect(const Vector3& incidentVector, const Vector3& normal) {
    return incidentVector - 2 * dot(incidentVector, normal) * normal;
}

class Metal : public Material {
public:
    Vector3 albedo;
    float fuzz;

    Metal(const Vector3 &newAlbedo, float newFuzz) : albedo(newAlbedo) {
        fuzz = newFuzz < 1 ? newFuzz : 1;
    }
    virtual bool scatter(const Ray &incidentRay, const HitRecord &hitRecord, Vector3 &attenuation,
                 Ray &scatteredRay) const {
        Vector3 reflected = reflect(unitVector(incidentRay.direction()), hitRecord.normal);
        scatteredRay = Ray(hitRecord.position, reflected + fuzz * randomInUnitSphere());
        attenuation = this->albedo;
        return (dot(scatteredRay.direction(), hitRecord.normal) > 0);
    }
};

#endif //SIMPLERAYTRACER_MATERIAL_H
