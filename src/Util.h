#pragma once

#include <stdlib.h>
#include <iterator>
#include <algorithm>
#include <limits>
#include <math.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>

#include "Pigment.h"
#include "vec3.h"
#include "Light.h"
#include "Object.h"
#include "Sphere.h"
#include "Plane.h"


class Util {
    public:
        Util() {}

        static double randD(double val);
        static double phongDiffuse(double Kd, vec3 normal, vec3 light);
        static double max(double a, double b) { return a > b ? a : b; }
        static void gammaEncoder(Pigment& p, double gamma);
        static double detMatrix(glm::vec3 col1, glm::vec3 col2, glm::vec3 col3);
        static vec3 applyCTM(vec3 v, glm::mat4 cmt, float val);

    private:
        static bool inUnitSphere(vec3 pos);
        static vec3 getPointInUnitSphere();
        static double Shlick(double cos_theta, double ior);
};


double Util::detMatrix(glm::vec3 col1, glm::vec3 col2, glm::vec3 col3) {
    return col1.x * (col2.y * col3.z - col3.y * col2.z)
            - col2.x * (col1.y * col3.z - col3.y * col1.z)
            + col3.x * (col1.y * col2.z - col2.y * col1.z);
}

// generating a random float in range 0 - 1 with a shift default to 0
double Util::randD(double val = 0) {
    return static_cast<double>(rand()) / static_cast<double>(RAND_MAX) + val;
}

double Util::phongDiffuse(double Kd, vec3 normal, vec3 light) {
    normal.normalize();
    light.normalize();

    return max(0, normal.dot(light)) * Kd;
}



// check if the given vector is inside the unit sphere center at (0, 0, 0) or not
bool Util::inUnitSphere(vec3 pos) {
    if (pos.leng() <= 1)
        return true;
    return false;
}

// encode the color with a gamma value
void Util::gammaEncoder(Pigment& p, double gamma = 2.2) {
    p = p^(1/gamma);
}

vec3 Util::getPointInUnitSphere() {
    vec3 s;

    do {
        s = vec3(Util::randD(-0.5) * 2, Util::randD(-0.5) * 2, Util::randD(-0.5) * 2);
    }  while (!inUnitSphere(s));
    return s;
}

double Util::Shlick(double cos_theta, double ior) {
    double r0 = (1.0 - ior) / (1.0 + ior);
    r0 *= r0;
    return r0 + (1.0 - r0) * pow(1 - cos_theta, 5);
}


vec3 Util::applyCTM(vec3 v, glm::mat4 cmt, float val) {
    glm::vec4 res = cmt * glm::vec4(v.x(), v.y(), v.z(), val);
    return vec3(res.x, res.y, res.z);
}