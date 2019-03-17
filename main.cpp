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

// Randomly generate a scene
Hitable* randomScene() {
    int n = 500;
    Hitable** list = new Hitable*[n + 1];
    list[0] = new Sphere(Vector3(0, -1000, 0), 1000, new Lambertian(Vector3(0.5, 0.5, 0.5))); // Ground
    int i = 1;
    for (int a = -11; a < 11; ++a) {
        for (int b = -11; b < 11; ++b) {
            float material = drand48();
            Vector3 center(a + 0.9 * drand48(), 0.2, b + 0.9 * drand48());
            if ((center - Vector3(4, 0.2, 0)).length() > 0.9) { // Diffuse
                if (material < 0.8) { // Diffuse
                    list[i++] = new Sphere(center, 0.2, new Lambertian(Vector3(drand48() * drand48(),
                                                                               drand48() * drand48(),
                                                                               drand48() * drand48())));
                } else if (material < 0.95) { // Metal
                    list[i++] = new Sphere(center, 0.2, new Metal(Vector3(0.5 * (1 + drand48()), 0.5 * (1 + drand48()),
                                                                          0.5 * (1 + drand48())), 0.5 * drand48()));
                } else { // Glass
                    list[i++] = new Sphere(center, 0.2, new Dielectric(1.5));
                }
            }
        }
    }
    list[i++] = new Sphere(Vector3(0, 1, 0), 1.0, new Dielectric(1.5));
    list[i++] = new Sphere(Vector3(-4, 1, 0), 1.0, new Lambertian(Vector3(0.4, 0.2, 0.1)));
    list[i++] = new Sphere(Vector3(4, 1, 0), 1.0, new Metal(Vector3(0.7, 0.6, 0.5)));
    return new HitableList(list, i);
}

int main() {
    std::ifstream cin("./test.ppm");
    std::ofstream cout("./test.ppm");

    int xLength = 1200;
    int yLength = 800;
    int sampleCount = 10;
    cout << "P3\n" << xLength << " " << yLength << "\n255\n";

    Vector3 lookFrom(13, 2, 3);
    Vector3 lookAt(0, 0, 0);
    float distanceToFocus = 10;
    float aperture = 0.1;
    Camera camera(lookFrom, lookAt, Vector3(0, 1, 0), 20, float(xLength) / float(yLength), aperture, distanceToFocus);
    Hitable *world = randomScene();

    for (int j = yLength - 1; j >= 0; --j) {
        for (int i = 0; i < xLength; ++i) {
            Vector3 pixColor(0, 0, 0);
            for (int s = 0; s < sampleCount; ++s) { // Anti-alias by randomly sampling for one pixel
                float u = float(i + drand48()) / float(xLength); // drand48() returns value in range [0, 1)
                float v = float(j + drand48()) / float(yLength);
                Ray ray = camera.getRay(u, v);
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