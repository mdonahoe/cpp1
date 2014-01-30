#pragma once
#include "RigidBody.h"

class Quadrotor {
public:
    Quadrotor();
    void desire(const Vector3f&, const Vector3f&);
    void update(float);
    void draw();
private:
    RigidBody m_body;
    void control(float, float, float, float);
};
