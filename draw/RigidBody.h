/*
 * Thanks to http://www.pixar.com/companyinfo/research/pbm2001/pdf/notesg.pdf
 * for the implementation ideas
 */

#pragma once

#include <Eigen/Core>

using namespace Eigen;

class RigidBody {
    public:
        RigidBody();// moment of inertia, size?
        const Vector3f& GetPosition();
        void SetPosition(const Vector3f&);

        const Vector3f& GetVelocity();
        void SetVelocity(const Vector3f&);

        void AddBodyForce(const Vector3f&, const Vector3f&);
        // force is at a point?
        //
        void AddTorque(const Vector3f&);
        // torque at a point?

        void update(float);

        /* constant */
        float mass;
        Matrix3f Ibody, Ibodyinv;

        /* State */
        Vector3f x;
        Matrix3f R;
        Vector3f P, L;

        /* Derived */
        Matrix3f Iinv;
        Vector3f v, omega;

        /* Computed */
        Vector3f force, torque;

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
};

Matrix3f Star(const Vector3f&);
