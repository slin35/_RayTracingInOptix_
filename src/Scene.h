#pragma once

#include <vector>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <memory>

#include "Camera.h"
#include "Sphere.h"
#include "Light.h"
#include "Plane.h"
#include "Object.h"

class Scene {
public:
    Scene(int shadingModel = 0) { this->shadingModel = shadingModel; }

    void addCamera(Camera* camera) {
        cameras.push_back(camera);
    }

    void addSphere(Sphere* sphere) {
        spheres.push_back(sphere);
        objects.push_back(sphere);
    }

    void addLight(Light* light) {
        if (light->isAreaLight())
            lights.push_back(light);
        objects.push_back(light);
    }

    void addPlane(Plane* plane) {
        planes.push_back(plane);
        objects.push_back(plane);
    }

public:

    std::vector<Camera*> cameras;
    std::vector<Sphere*> spheres;
    std::vector<Light*> lights;
    std::vector<Plane*> planes;
    std::vector<Object*> objects;
    int shadingModel;
};