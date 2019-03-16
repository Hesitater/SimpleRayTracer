#include <iostream>
#include <fstream>
#include <float.h>
#include "Sphere.h"
#include "HitableList.h"
#include "Camera.h"
#include "Material.h"

Vector3 color(const Ray &ray, Hitable *world, int depth) {
    HitRecord hitRecord;
    if (world->hit(ray, 0.001, MAXFLOAT, hitRecord)) {
        Ray scatteredRay;
        Vector3 attenuation;
        if (depth < 50 && hitRecord.materialPointer->scatter(ray, hitRecord, attenuation, scatteredRay)) {
            return attenuation * color(scatteredRay, world, depth + 1);
        } else {
            return Vector3(0, 0, 0);
        }
    } else {
        Vector3 unitDirection = unitVector(ray.direction());
        float k = 0.5 * (unitDirection.y() + 1.0);
        return (1.0 - k) * Vector3(1.0, 1.0, 1.0) + k * Vector3(0.5, 0.7, 1.0);
    }
}

int main() {
    std::ifstream cin("./test.ppm");
    std::ofstream cout("./test.ppm");

    int xLength = 200;
    int yLength = 100;
    int sampleCount = 100;
    cout << "P3\n" << xLength << " " << yLength << "\n255\n";
    Camera camera;
    Hitable* list[4];
    list[0] = new Sphere(Vector3(0, 0, -1), 0.5, new Lambertian(Vector3(0.8, 0.3, 0.3)));
    list[1] = new Sphere(Vector3(0, -100.5, -1), 100, new Lambertian(Vector3(0.8, 0.8, 0.0)));
    list[2] = new Sphere(Vector3(1, 0, -1), 0.5, new Metal(Vector3(0.8, 0.6, 0.2), 0.3));
    list[3] = new Sphere(Vector3(-1, 0, -1), 0.5, new Metal(Vector3(0.8, 0.8, 0.8), 1));
    Hitable *world = new HitableList(list, 4);

    for (int j = yLength - 1; j >= 0; --j) {
        for (int i = 0; i < xLength; ++i) {
            Vector3 pixColor(0, 0, 0);
            for (int s = 0; s < sampleCount; ++s) { // Anti-alias by randomly sampling for one pixel
                float u = float(i + drand48()) / float(xLength); // drand48() returns value in range [0, 1)
                float v = float(j + drand48()) / float(yLength);
                Ray ray = camera.getRay(u, v);
                Vector3 p = ray.pointAtParameter(2.0);
                pixColor += color(ray, world, 0);
            }
            pixColor /= float(sampleCount);
            pixColor = Vector3(sqrt(pixColor[0]), sqrt(pixColor[1]), sqrt(pixColor[2]));
            int ir = int(255.99 * pixColor[0]);
            int ig = int(255.99 * pixColor[1]);
            int ib = int(255.99 * pixColor[2]);
            cout << ir << " " << ig << " " << ib << "\n";
        }
    }
    return 0;
}