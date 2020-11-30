#pragma once

#include <algorithm>
#include <iostream>

#include "vec3.h"
#include "Pigment.h"
#include "Object.h"

class Light : public Object {
    public:
        Light() {}

        Light(vec3 position, Pigment pigment) :
            position(position), pigment(pigment) {}

        gdt::vec3f getPosition() { return gdt::vec3f((float)position.x(), (float)position.y(), (float)position.z()); }
     //   Pigment getPigment() { return pigment; }
        gdt::vec3f getPigment() { return gdt::vec3f((float)pigment.r, (float)pigment.g, (float)pigment.b); }
        gdt::vec3f getV1() { return gdt::vec3f((float)v1.x(), (float)v1.y(), (float)v1.z()); }
        gdt::vec3f getV2() { return gdt::vec3f((float)v2.x(), (float)v2.y(), (float)v2.z()); }
        bool isAreaLight() { return areaLight; }

        void setPosition(vec3 position) { this->position = position; }
        void setPigment(vec3 pigment) { this->pigment.setPigment(pigment); }
        void setV1(vec3 v1) { this->v1 = v1; this->areaLight = true; }
        void setV2(vec3 v2) { this->v2 = v2; }


        virtual Pigment getColor() { return pigment; }
        virtual int getSurfaceType() { return 2; }

        virtual double getFuzzy() { return 0; }
        virtual double getIor() { return 0; }
        virtual void setSurfaceType(int type) { this->type = type; };

    private:
        vec3 position;
        Pigment pigment{0.0f, 0.0f, 0.0f};
        vec3 v1;
        vec3 v2;
        bool areaLight = false;
        int type;
};