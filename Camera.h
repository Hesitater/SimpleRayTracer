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

    Camera() {
        lowerLeftCorner = Vector3(-2.0, -1.0, -1.0);
        horizontal = Vector3(4.0, 0.0, 0.0);
        vertical = Vector3(0.0, 2.0, 0.0);
        origin = Vector3(0.0, 0.0, 0.0);
    }
    Ray getRay(float u, float v) { return Ray(origin, lowerLeftCorner + u * horizontal + v * vertical); }
};

#endif //SIMPLERAYTRACER_CAMERA_H
