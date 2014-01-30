#pragma once
#include "RigidBody.h"

class Quadrotor {
public:
    Quadrotor(float);
    void desire(const Vector3f&, const Vector3f&);
    void update(float);
    void draw();
private:
    RigidBody body;
    float radius;
    void motors(float, float, float, float);
};
