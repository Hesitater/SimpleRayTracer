//
// Created by 易子沐 on 2019/3/16.
//

#ifndef SIMPLERAYTRACER_CAMERA_H
#define SIMPLERAYTRACER_CAMERA_H

#include "Ray.h"

class Camera {
public:
    Vector3 lowerLeftCorner; // Right-hand rule, Z depth is -1
    Vector3 horizontal;
    Vector3 vertical;
    Vector3 origin;

    Camera(Vector3 lookFrom, Vector3 lookAt, Vector3 viewUp, float fovDegree, float aspect) {
        Vector3 u, v, w; // Local coordinates of x, y, z
        float theta = fovDegree * M_PI / 180;
        float halfHeight = tan(theta / 2);
        float halfWidth = aspect * halfHeight;
        origin = lookFrom;
        w = unitVector(lookFrom - lookAt);
        u = unitVector(cross(viewUp, w));
        v = cross(w, u);
        lowerLeftCorner = Vector3(-halfWidth, -halfHeight, -1.0);
        lowerLeftCorner = origin - halfWidth * u - halfHeight * v - w;
        horizontal = 2 * halfWidth * u;
        vertical = 2 * halfHeight * v;
    }
    Ray getRay(float u, float v) { return Ray(origin, lowerLeftCorner + u * horizontal + v * vertical - origin); }
};

#endif //SIMPLERAYTRACER_CAMERA_H
