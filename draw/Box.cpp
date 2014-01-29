#include "Box.h"
#include "shape.h"
#include "glheaders.h"


Box::Box(float l, float h, float w): m_length(l),
                                     m_height(h),
                                     m_width(w),
                                     m_roll(0.0),
                                     m_pitch(0.0),
                                     m_yaw(0.0),
                                     m_origin(0,0,0) {};

void Box::draw(){
    glPushMatrix();

    // the origin is the center of the box
    std::cout << "origin = " << m_origin << std::endl;
    glTranslatef(m_origin.x, m_origin.y, m_origin.z);


    glRotatef(m_roll,  1,0,0);
    glRotatef(m_yaw,   0,1,0);
    glRotatef(m_pitch, 0,0,1);

    // scale by the size?
    glScalef(0.5 * m_length, 0.5 * m_height, 0.5 * m_width);
  

    Cube();

    glPopMatrix();
};

void Box::SetOrigin(const Vector &origin){
    m_origin = origin;
};

void Box::SetRoll(float r){
    m_roll = r;
};

void Box::SetYaw(float y){
    m_yaw = y;
};
