#include "RigidBody.h"
#include <Eigen/LU>

RigidBody::RigidBody(float m, const Matrix3f &I){
    mass = m;
    Ibody = I;
    Ibodyinv = I.inverse();

    R << 1, 0, 0,
         0, 1, 0,
         0, 0, 1;
    x.setZero();
    P.setZero();
    L.setZero();

    force.setZero();
    torque.setZero();
};

const static Vector3f GRAVITY(0.0, -1.0, 0.0);

void RigidBody::update(float dt){
    //shitty euler integration
    P += dt * force;
    L += dt * torque;

    v = P / mass;
    Iinv = R * Ibodyinv * R.transpose();
    omega = Iinv * L;

    x += dt * v;
    R += dt * (Skew(omega) * R);

    // reset computed values (is there a better way to do this)
    force = GRAVITY;
    torque = Vector3f(0.0, 0.0, 0.0);
};

Matrix3f Skew(const Vector3f &v){
    Matrix3f out;
    out <<    0, -v[2],  v[1],
           v[2],     0, -v[0],
          -v[1],  v[0],     0;
    return out;
};

// inertia tensor of block on page 27 (only diagonal terms)
void RigidBody::AddTorque(const Vector3f& t){
    torque += t;
};

void RigidBody::AddBodyForce(const Vector3f& f, const Vector3f& p){
    force += f;// needs to be transformed from body to world coordinates
    // compute the torque based on f x p;
    torque += Vector3f(0.0, 0.0, 0.0);
};
