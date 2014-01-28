#pragma once
#include "Vector.h"

class Box {
    public:
        Box(float, float, float);
        float volume();
        void SetOrigin(const Vector&);
        void SetRoll(float);
        void SetYaw(float);
        void draw();

    private:
        float m_length;
        float m_height;
        float m_width;
        float m_roll;
        float m_pitch;
        float m_yaw;
        Vector m_origin;
};
