#pragma once
#include "Vector.h"

class Box {
    public:
        Box(float l, float w, float h);
        float volume();
        void SetOrigin(const Vector &origin);
        void draw();

    private:
        float m_length;
        float m_width;
        float m_height;
        Vector m_origin;
};
