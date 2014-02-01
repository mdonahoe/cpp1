#include "Quadrotor.h"
#include "glheaders.h"
#include "shape.h"


Quadrotor::Quadrotor(float r): body(1, Matrix3f()), radius(r) {
    // now REALLY set it.
    // take into account the radius and x-cross
    Matrix3f I;
    I << 1, 0, 0,
         0, 1, 0,
         0, 0, 1;
    body = RigidBody(2, I);
};

void Quadrotor::motors(float a, float b, float c, float d){
    Vector3f ar, br, cr, dr;
    Vector3f af, bf, cf, df;

    float R = radius; // rotor radius at edges
    float H = 0; // rotors in plane with center of mass

    /*
     *   a
     * d   b
     *   c
     */

    ar <<  R, H, 0;
    br <<  0, H, R;
    cr << -R, H, 0;
    dr <<  0, H,-R;

    af <<  0, a, 0;
    bf <<  0, b, 0;
    cf <<  0, c, 0;
    df <<  0, d, 0;


    body.AddBodyForce(af, ar);
    body.AddBodyForce(bf, br);
    body.AddBodyForce(cf, cr);
    body.AddBodyForce(df, dr);

    // total torque
    Vector3f t;
    t << 0, a + c - (b + d), 0;
    Vector3f world_t = body.R * t;
    body.AddTorque(world_t);
};

void Quadrotor::draw(){
    float h = 0.2;
    float w = 0.2;
    glPushMatrix();
    glMultMatrixf(body.R, body.x);

    glPushMatrix();
    Prism(2 * radius, h, w);
    glPopMatrix();

    glPushMatrix();
    Prism(w, h, 2 * radius);
    glPopMatrix();

    glPopMatrix();
};

void Quadrotor::update(float dt){
    body.update(dt);
};


void Quadrotor::manual(const Vector3f &stick){
    float thrust = 1;
    float pitch = stick[0] / 20.0;
    float roll = stick[2] / 20.0;
    float yaw = 0;
    motors(thrust + yaw + pitch,
           thrust - yaw + roll,
           thrust + yaw - pitch,
           thrust - yaw - roll);
};

void Quadrotor::desire(const Vector3f &position, const Vector3f &eye){
    // GOAL: move somewhere and look at something else

    // transform the diff vector into bodyspace coordinates
    Matrix3f Rt = body.R.transpose();
    Vector3f dx = position - body.x;

    // tunable params
    float p = 2;
    float d = 0.5;

    // first attempt at a "control" vector, though it doesnt work
    Vector3f c = p * (Rt * dx) - d * (Rt * body.omega) - d * (Rt * body.v);

    // logic control inputs
    float yaw = 0;
    float pitch = 0.01;
    float thrust = 1;
    float roll = 0.0;

    motors(thrust + yaw + pitch,
           thrust - yaw + roll,
           thrust + yaw - pitch,
           thrust - yaw - roll);

};

