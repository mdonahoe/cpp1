#include <cmath>
#include "Vector.h"

Vector::Vector(float x_, float y_, float z_=0.0): x(x_), y(y_), z(z_) {};
Vector::Vector(const Vector &other): x(other.x), y(other.y), z(other.z) {};

Vector operator*(const Vector &v, float c){
    return Vector(c * v.x, c * v.y, c * v.z);
};

Vector operator*(float c, const Vector &v){
    return v * c;
};

Vector operator+(const Vector& a, const Vector& b){
    return Vector(a.x + b.x, a.y + b.y, a.z + b.z);
};

Vector operator-(const Vector& a, const Vector& b){
    return Vector(a.x - b.x, a.y - b.y, a.z - b.z);
};

std::ostream& operator<<(std::ostream &out, Vector &v){
    out << "<" << v.x << ", " << v.y << ", " << v.z << ">";
    return out;
};

Vector cross(const Vector& a, const Vector& b){
    return Vector(a.y * b.z - a.z * b.y,
                  a.z * b.x - a.x * b.z,
                  a.x * b.y - a.y * b.z);
};

float dot(const Vector& a, const Vector& b){
    return a.x * b.x + a.y * b.y + a.z * b.z;
};

float mag(const Vector& v) {
    return sqrt(dot(v, v));
};

Vector norm(const Vector& v){
    return v * mag(v);
};
