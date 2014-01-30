#include "Quadrotor.h"

#include <iostream>
using namespace std;

Quadrotor::Quadrotor(): m_body(1, Matrix3f()) {
    // now REALLY set it.
    Matrix3f I;
    I << 1, 0, 0,
         0, 1, 0,
         0, 0, 1;
    m_body = RigidBody(2, I);
};

void Quadrotor::control(float a, float b, float c, float d){
    Vector3f ar, br, cr, dr;
    Vector3f af, bf, cf, df;

    float W = 1;
    float H = 1;
    float L = 1;

    /*
     * a b
     * c d
     */

    ar <<  L,H, W;
    br << -L,H, W;
    cr <<  L,H,-W;
    dr << -L,H,-W;
    af << 0, a, 0;
    bf << 0, b, 0;
    cf << 0, c, 0;
    df << 0, d, 0;

    m_body.AddBodyForce(af, ar);
    m_body.AddBodyForce(bf, br);
    m_body.AddBodyForce(cf, cr);
    m_body.AddBodyForce(df, dr);

    // total torque
    Vector3f t;
    t << 0, a + d - (b + c) , 0;
    Vector3f world_t = m_body.R * t;
    m_body.AddTorque(world_t);
};

void Quadrotor::draw(){
    m_body.draw();
};
void Quadrotor::update(float dt){
    m_body.update(dt);
};

void Quadrotor::desire(const Vector3f &position, const Vector3f &direction){
    Vector3f dx = position - m_body.x;
    Vector3f forward = m_body.R.col(0);
    Vector3f up = m_body.R.col(1);
    cout << "up = " << up << endl;
    forward.normalize();
    float dangle = forward.cross(direction)(1);
    float spin = m_body.omega(1);
    float speed = m_body.v(1);
    float p = 2;
    float d = 0.5;
    float front = 0.1;
    float thrust = p * dx(1) + d * (0 - speed);
    float twist = p * (dangle) + d * (0 - spin);
    control(thrust + twist + front, thrust - twist - front,
            thrust - twist + front, thrust + twist - front);
};
