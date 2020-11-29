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

        vec3 getPosition() { return position; }
        Pigment getPigment() { return pigment; }
        vec3 getV1() { return v1; }
        vec3 getV2() { return v2; }
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