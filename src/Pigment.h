#pragma once

#include <iostream>
#include <math.h>

#include "vec3.h"

class Pigment {
    public:
        Pigment() : r(0), g(0), b(0) {}

        Pigment(double r, double g, double b) : 
            r(r), g(g), b(b) {}

        Pigment(vec3 pigment) : 
            r(pigment.x()), g(pigment.y()), b(pigment.z()) {}

        friend std::ostream& operator<<(std::ostream& os, const Pigment& p) {
			os << "<" << p.r << ", " << p.g << ", " << p.b << ">";
			return os;
		}

        void setPigment(vec3 pigment) {
            r = pigment.x();
            g = pigment.y();
            b = pigment.z();
        }

        Pigment operator+(const Pigment p) const {
            Pigment res;
            res.r = p.r + this->r;
            res.g = p.g + this->g;
            res.b = p.b + this->b;
            return res;
        }

        Pigment operator/(const double Sc) const {
            Pigment res;
            res.r = this->r / Sc;
            res.g = this->g / Sc;
            res.b = this->b / Sc;
            return res;
        }

        Pigment operator*(const double Sc) const {
            Pigment res;
            res.r = this->r * Sc;
            res.g = this->g * Sc;
            res.b = this->b * Sc;
            return res;
        }

        Pigment operator*(const Pigment p) const {
            Pigment res;
            res.r = this->r * p.r;
            res.g = this->g * p.g;
            res.b = this->b * p.b;
            return res;
        }

        Pigment operator^(const double exponent) const {
            Pigment res;
            res.r = pow(this->r, exponent);
            res.g = pow(this->g, exponent);
            res.b = pow(this->b, exponent);
            return res;
        }

    public:
        double r, g, b;
};