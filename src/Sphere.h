#pragma once

#include <vector>
#include <iostream> 
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtx/string_cast.hpp>
#include <string>

#include "Pigment.h"
#include "vec3.h"
#include "Object.h"


class Sphere : public Object {
    public:
        Sphere() {}

        Sphere(vec3& center, float radius, Pigment& pigment) :
            center(center), radius(radius), pigment{pigment} {}


        void setCenter(vec3 center) { this->center = center; }
        void setRadius(double raidus) { this->radius = raidus; }
        void setPigment(vec3 pigment) { this->pigment.setPigment(pigment); }
        void setFuzzy(double fuzzy) { 
            this->fuzzy = fuzzy; 
            this->type = 1;
        }
        void setIor(double ior) {
            this->ior = ior;
            this->type = 3;
        }
        void setScale(vec3 scale) { 
            this->scale = scale;
            S = glm::scale(glm::mat4(1.0f), glm::vec3(scale.x(), scale.y(), scale.z()));
            ctm = S * ctm;
        }
        void setRotate(vec3 rotate) { 
            this->rotate = rotate;
            glm::vec3 axis(0.0f);
            float angle = 0.0f;
            if (rotate.x() != 0) {
                axis.x = 1.0;
                angle = rotate.x();
            }
            else if (rotate.y() != 0) {
                axis.y = 1.0;
                angle = rotate.y();
            }
            else if (rotate.z() != 0) {
                axis.z = 1.0;
                angle = rotate.z();
            }
            angle = (float)angle / 180.0 * 3.14;
            R = glm::rotate(glm::mat4(1.0f), angle, axis);
            ctm = R * ctm;
        }
        void setTranslate(vec3 translate) { 
            this->translate = translate; 
            T = glm::translate(glm::mat4(1.0f), glm::vec3(translate.x(), translate.y(), translate.z()));
            ctm = T * ctm;
        }

        void transCTM() {
            invCTM = glm::inverse(ctm);
            invTransCTM = glm::inverseTranspose(ctm);
            transposeCTM = glm::transpose(ctm);
        }
      
        void setTextureImg(std::string img) {
            this->img = img;
        }

        std::string getTexturte() { return img; }

        gdt::vec3f getDiffuseColor() { return gdt::vec3f((float)pigment.r, (float)pigment.g, (float)pigment.b); }

    //    vec3 getCenter() const { return center; }
        gdt::vec3f getCenter() { return gdt::vec3f((float)center.x(), (float)center.y(), (float)center.z()); }
        float getRadius() const { return (float)radius; }
        Pigment getpigment() const { return pigment; }

        virtual double getFuzzy() { return fuzzy; }
        virtual double getIor() { return ior; }

        virtual Pigment getColor() { return pigment; }
        virtual int getSurfaceType() { return type; }
        virtual void setSurfaceType(int type) { this->type = type; }


    private:
        vec3 center;
        double radius = 0;
        Pigment pigment{1.0f, 1.0f, 1.0f};
        double fuzzy = 0;
        int type = 0;
        double ior;
        vec3 scale;
        vec3 rotate;
        vec3 translate;
        glm::mat4 ctm = glm::mat4(1.0f);
        glm::mat4 invCTM = glm::mat4(1.0f);
        glm::mat4 invTransCTM = glm::mat4(1.0f);
        glm::mat4 transposeCTM = glm::mat4(1.0f);
        glm::mat4 S = glm::mat4(1.0f);
        glm::mat4 R = glm::mat4(1.0f);
        glm::mat4 T = glm::mat4(1.0f);
        std::string img;
        
};

