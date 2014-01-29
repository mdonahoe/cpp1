#include "RigidBody.h"
#include <Eigen/Geometry>
#include <Eigen/LU>
#include "shape.h"
#include "glheaders.h"
#include <iostream>

using namespace std;

static int ntimes = 0;
const static Vector3f GRAVITY(0.0, -10.0, 0.0);

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


void RigidBody::update(float dt){
    //shitty euler integration
    // cout << "force = " << force << endl << "---" << endl;

    P += dt * force;
    L += dt * torque;

    v = P / mass;
    Iinv = R * Ibodyinv * R.transpose();
    omega = Iinv * L;

    x += dt * v;
    R += dt * (Skew(omega) * R);
    if (++ntimes == 3){
        ntimes = 0;
        renormalize();
    }

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

void RigidBody::AddBodyForce(const Vector3f& f, const Vector3f& r){
    // needs to be transformed from body to world coordinates
    Vector3f world_f = R * f;
    Vector3f world_r = R * r;

    force += world_f;
    torque += world_r.cross(world_f);
};

void RigidBody::draw(){
    // cout << R << endl << "----" <<  endl;
    GLfloat m[16];

    m[0] = R(0,0);
    m[1] = R(1,0);
    m[2] = R(2,0);
    m[3] = 0.0;

    m[4] = R(0,1);
    m[5] = R(1,1);
    m[6] = R(2,1);
    m[7] = 0.0;

    m[8] = R(0,2);
    m[9] = R(1,2);
    m[10] = R(2,2);
    m[11] = 0.0;

    m[12] = 0.0; 
    m[13] = 0.0; 
    m[14] = 0.0; 
    m[15] = 1.0; 

    glPushMatrix();
    glTranslatef(x(0), x(1), x(2));
    glMultMatrixf(m);
    Cube();
    glPopMatrix();
};

/*
 * v(t) = P(t) / M;
 * I(t) = R(t)*Ibody*R(t).transpose();
 * I(t)^-1 = R(t)*(Ibody^-1)*R(t).transpose();
 * w(t) = I(t).inv() * L(t);
 * F(t) = total linear force
 *
 * d/dt(x) = v(t);
 * d/dt(R) = w(t)*R(t);
 * d/dt(P) = F(t);
 * d/dt(L) = tau(t);
 */

void printq(const Quaternionf &q){
    cout << "quat = " << q.x() << "," << q.y() << "," << q.z() << "," << q.w() << endl;
};

void RigidBody::renormalize(){
    // calculate how bad it is
    // cout << "det = " << R.determinant() << endl;

    // I dont like this.
    // I have seen other ones
    Quaternionf q(R);
    q.normalize();
    R = q.toRotationMatrix();

    // cout << "post det = " << R.determinant() << endl;
};

