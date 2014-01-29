#include "Quadrotor.h"

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

    m_body.AddBodyForce(af, ar);
    m_body.AddBodyForce(bf, br);
    m_body.AddBodyForce(cf, cr);
    m_body.AddBodyForce(df, dr);

    // total torque
    Vector3f t;
    t(1) = a + c - (b + d);
    m_body.AddTorque(m_body.R * t);
};
