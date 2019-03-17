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

    Metal(const Vector3 &newAlbedo) : albedo(newAlbedo) {fuzz = 0.0;}

    Metal(const Vector3 &newAlbedo, float newFuzz) : albedo(newAlbedo) {
        fuzz = newFuzz < 1 ? newFuzz : 1;
    }
    virtual bool scatter(const Ray &incidentRay, const HitRecord &hitRecord, Vector3 &attenuation,
                 Ray &scatteredRay) const {
        Vector3 reflected = reflect(unitVector(incidentRay.direction()), hitRecord.normal);
        scatteredRay = Ray(hitRecord.position, reflected);
        attenuation = this->albedo;
        return (dot(scatteredRay.direction(), hitRecord.normal) > 0);
    }
};

bool refract(const Vector3& incident, const Vector3& normal, float niOverNt, Vector3& refracted) {
    Vector3 uv = unitVector(incident);
    float dt = dot(uv, normal);
    float discriminant = 1.0 - niOverNt * niOverNt * (1 - dt * dt);
    if (discriminant > 0) {
        refracted = niOverNt * (uv - normal * dt) - normal * sqrt(discriminant);
        return true;
    } else {
        return false;
    }
}

float schlick(float cosine, float refractIndex) {
    float r0 = (1 - refractIndex) / (1 + refractIndex);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow((1 - cosine), 5);
}

class Dielectric : public Material {
public:
    float refractIndex;

    Dielectric(float newRefractIndex) : refractIndex(newRefractIndex) {}

    virtual bool scatter(const Ray &incidentRay, const HitRecord &hitRecord, Vector3 &attenuation,
                 Ray &scatteredRay) const {
        Vector3 outwardNormal;
        Vector3 reflected = reflect(incidentRay.direction(), hitRecord.normal);
        float niOverNt;
        attenuation = Vector3(1.0, 1.0, 1.0);
        Vector3 refracted;
        float reflectProb;
        float cosine;
        if (dot(incidentRay.direction(), hitRecord.normal) > 0) {
            outwardNormal = - hitRecord.normal;
            niOverNt = this->refractIndex;
            cosine = this->refractIndex * dot(incidentRay.direction(), hitRecord.normal) / incidentRay.direction().length();
        } else {
            outwardNormal = hitRecord.normal;
            niOverNt = 1.0 / this->refractIndex;
            cosine = -dot(incidentRay.direction(), hitRecord.normal) / incidentRay.direction().length();
        }
        if (refract(incidentRay.direction(), outwardNormal, niOverNt, refracted)) {
            reflectProb = schlick(cosine, this->refractIndex);
        } else {
            reflectProb = 1.0;
        }
        if (drand48() < reflectProb) {
            scatteredRay = Ray(hitRecord.position, reflected);
        } else {
            scatteredRay = Ray(hitRecord.position, refracted);
        }
        return true;
    }
};

#endif //SIMPLERAYTRACER_MATERIAL_H
