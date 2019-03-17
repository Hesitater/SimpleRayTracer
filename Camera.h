//
// Created by 易子沐 on 2019/3/16.
//

#ifndef SIMPLERAYTRACER_CAMERA_H
#define SIMPLERAYTRACER_CAMERA_H

#include "Ray.h"

Vector3 randomInUnitDisk() {
    Vector3 p;
    do {
        p = 2.0 * Vector3(drand48(), drand48(), 0) - Vector3(1, 1, 0);
    } while (dot(p, p) >= 1.0);
    return p;
}
class Camera {
public:
    Vector3 lowerLeftCorner; // Right-hand rule, Z depth is -1
    Vector3 horizontal;
    Vector3 vertical;
    Vector3 origin;
    Vector3 u, v, w; // Local coordinates of x, y, z
    float lensRadius;

    Camera(Vector3 lookFrom, Vector3 lookAt, Vector3 viewUp, float fovDegree, float aspect, float aperture,
               float focusDistance) {
        lensRadius = aperture / 2;
        float theta = fovDegree * M_PI / 180;
        float halfHeight = tan(theta / 2);
        float halfWidth = aspect * halfHeight;
        origin = lookFrom;
        w = unitVector(lookFrom - lookAt);
        u = unitVector(cross(viewUp, w));
        v = cross(w, u);
        lowerLeftCorner = origin - halfWidth * focusDistance * u - halfHeight * focusDistance * v - focusDistance * w;
        horizontal = 2 * halfWidth * focusDistance * u;
        vertical = 2 * halfHeight * focusDistance * v;
    }
    Ray getRay(float s, float t) {
        Vector3 rd = lensRadius * randomInUnitDisk();
        Vector3 offset = u * rd.x() + v * rd.y();
        return Ray(origin + offset, lowerLeftCorner + s * horizontal + t * vertical - origin - offset);
    }
};

#endif //SIMPLERAYTRACER_CAMERA_H
