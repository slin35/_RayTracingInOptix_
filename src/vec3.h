#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

class vec3 {
	public:
		vec3(double in1, double in2, double in3) : val{in1, in2, in3} {}
		vec3() : val{0,0,0} {} //default constructor
		vec3(double in) : val{in,in,in} {} //alt constructor

		//getters
		double x() const { return val[0]; }
		double y() const { return val[1]; }
		double z() const { return val[2]; }
		void setX(double inX) { val[0] = inX; }
		void setY(double inY) { val[1] = inY; }
		void setZ(double inZ) { val[2] = inZ; }

		//overload operators
		vec3& operator+=(const vec3 &v) {
			val[0] += v.val[0];
			val[1] += v.val[1];
			val[2] += v.val[2];
			return *this;
		}

		//mult by scalar

		vec3& operator*=(const double Sc) {
			val[0] *= Sc;
			val[1] *= Sc;
			val[2] *= Sc;
			return *this;
		}

		vec3& operator/=(const double Sc) {
			val[0] /= Sc;
			val[1] /= Sc;
			val[2] /= Sc;
			return *this;
		}

		vec3 operator*(const vec3 v) const {
			vec3 res(val[0] * v.val[0], val[1] * v.val[1], val[2] * v.val[2]);
			return res;
		} 

		vec3 operator*(const float Sc) const {
			vec3 res(val[0] * Sc, val[1] * Sc, val[2] * Sc);
			return res;
		}

		vec3 operator-(const vec3 v) const {
			vec3 res(val[0] - v.val[0], val[1] - v.val[1], val[2] - v.val[2]);
			return res;
		}

		vec3 operator+(const vec3 v) const {
			vec3 res(val[0] + v.val[0], val[1] + v.val[1], val[2] + v.val[2]);
			return res;
		}

		vec3 cross(const vec3 v) const{
			vec3 c;
			c.val[0] = val[1] * v.val[2] - val[2] * v.val[1];
			c.val[1] = val[2] * v.val[0] - val[0] * v.val[2];
			c.val[2] = val[0] * v.val[1] - val[1] * v.val[0];
			return c;
		}	

		double dot(const vec3 v) {
			return val[0] * v.val[0] + val[1] * v.val[1] + val[2] * v.val[2];
		}

		void normalize() {
			double length = sqrt(pow(val[0], 2) + pow(val[1], 2) + pow(val[2], 2));
			val[0] /= length;
			val[1] /= length;
			val[2] /= length;
		}

		double leng() const {
			return std::sqrt(pow(val[0], 2) + pow(val[1], 2) + pow(val[2], 2));
		}

		friend std::ostream& operator<<(std::ostream& os, const vec3& v) {
			os << "<" << v.val[0] << ", " << v.val[1] << ", " << v.val[2] << ">";
			return os;
		}

	public:
		double val[3];
};

//Type aliases for vec3
using point3D = vec3; //3D point
using color = vec3; //RGB color

#endif
