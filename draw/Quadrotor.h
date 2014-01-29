#pragma once
#include "RigidBody.h"

class Quadrotor {
public:
    Quadrotor();
    // some sort of control input?
    RigidBody m_body;
    void control(float, float, float, float);
};
