/*
 * Thanks to http://www.pixar.com/companyinfo/research/pbm2001/pdf/notesg.pdf
 * for the implementation ideas
 */

#pragma once

#include <Eigen/Core>
#include <Eigen/Geometry>

using namespace Eigen;

class RigidBody {
public:
    RigidBody(float, const Matrix3f&);
    const Vector3f& GetPosition();
    void SetPosition(const Vector3f&);

    const Vector3f& GetVelocity();
    void SetVelocity(const Vector3f&);

    void AddBodyForce(const Vector3f&, const Vector3f&);
    // force is at a point?

    void AddTorque(const Vector3f&);
    // torque at a point?

    void update(float);
    void draw();

    /* Constant */
    float mass;
    Matrix3f Ibody, Ibodyinv;

    /* State */
    Matrix3f R;
    Vector3f x;
    Vector3f P, L;

    /* Derived */
    Matrix3f Iinv;
    Vector3f v, omega;

    /* Computed */
    Vector3f force, torque;

private:
    void renormalize();

};

Matrix3f Skew(const Vector3f&);
std::ostream& operator<<(std::ostream &out, Quaternionf &q);
void glMultMatrixf(const Matrix3f&, const Vector3f&);
