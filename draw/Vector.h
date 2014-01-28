#pragma once
#include <iostream>

class Vector {
    public:
        float x, y, z;
        Vector(float, float, float);
        Vector(const Vector&);
};
std::ostream& operator<<(std::ostream&, Vector&);

// math!
Vector operator*(const Vector&, float);
Vector operator*(float, const Vector&);
Vector operator+(const Vector&, const Vector&);
Vector operator-(const Vector&, const Vector&);

Vector cross(const Vector&, const Vector&);
Vector norm(const Vector&);
float dot(const Vector&, const Vector&);
float mag(const Vector&);
