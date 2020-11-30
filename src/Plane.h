#pragma once

#include "vec3.h"
#include "Pigment.h"
#include "Object.h"

class Plane : public Object {
    public:
        Plane() {}

        Plane(vec3 normal, double distance) :
            normal(normal), distance(distance) {}
    

        gdt::vec3f getNormal() { return gdt::vec3f((float)normal.x(), (float)normal.y(), (float)normal.z()); }
        float getDistance() { return (float)distance; }
        Pigment getPigment() { return pigment; }

        void setNormal(vec3 normal) { this->normal = normal; }
        void setDistance(double distance) { this->distance = distance; }
        void setPigment(vec3 pigment) { this->pigment.setPigment(pigment); }
        void setFuzzy(double fuzzy) { 
            this->fuzzy = fuzzy; 
            this->type = 1;
        }
        void setIor(double ior) {
            this->ior = ior;
            this->type = 3;
        }
       

        gdt::vec3f getPlaneColor() { return gdt::vec3f((float)pigment.r, (float)pigment.g, (float)pigment.b); }
        virtual Pigment getColor() { return pigment; }

        virtual int getSurfaceType() { return type; }
        virtual double getFuzzy() { return fuzzy; };
        virtual double getIor() { return ior; }
        virtual void setSurfaceType(int type) { this->type = type; }

    private:
        vec3 normal;
        double distance;
        Pigment pigment;
        double fuzzy = 0;
        int type = 0;
        double ior = 0;
};
