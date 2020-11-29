#pragma once

#include <vector>

#include "vec3.h"


class Camera {
    public:
        Camera() {}

        Camera(vec3& eye, vec3& up, vec3& right, vec3& lookAt) :
            eye(eye), up(up), right(right), lookAt(lookAt) {}

        void setEye(vec3 eye) { this->eye = eye; }
        void setUp(vec3 up) { this->up = up;}
        void setRight(vec3 right) { this->right = right; }
        void setLookAt(vec3 lookAt) { this->lookAt = lookAt; }

    //    vec3 getEye() const { return eye; }
     //   vec3 getUp() const { return up; }
     //   vec3 getRight() const { return right; }
    //    vec3 getLookAt() const { return lookAt; }

        gdt::vec3f getFrom() { return gdt::vec3f((float)eye.x(), (float)eye.y(), (float)eye.z()); }
        gdt::vec3f getAt() { return gdt::vec3f((float)lookAt.x(), (float)lookAt.y(), (float)lookAt.z()); }
        gdt::vec3f getUp() { return gdt::vec3f((float)up.x(), (float)up.y(), (float)up.z()); }


    private:
        vec3 eye{0, 0, 0};
        vec3 up{0, 1, 0};
        vec3 right{1, 0, 0};
        vec3 lookAt{0, 0, 0};
};