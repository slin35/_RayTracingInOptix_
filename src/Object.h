#pragma once

#include "vec3.h"
#include "Pigment.h"

class Object {
    public:
        Object() {}

       
        virtual Pigment getColor() = 0;
        virtual double getFuzzy() { return 0; }
        virtual int getSurfaceType() { return 0; }
        virtual double getIor() { return 0; }
        virtual void setSurfaceType(int type) {};

};