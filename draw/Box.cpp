#include "glheaders.h"
#include "Box.h"


GLfloat n[6][3] = {  /* Normals for the 6 faces of a cube. */
  {-1., 0.0, 0.0},
  {0.0, 1.0, 0.0},
  {1.0, 0.0, 0.0},
  {0.0, -1., 0.0},
  {0.0, 0.0, 1.0},
  {0.0, 0.0, -1.}
};

GLint faces[6][4] = {  /* Vertex indices for the 6 faces of a cube. */
  {0, 1, 2, 3},
  {3, 2, 6, 7},
  {7, 6, 5, 4},
  {4, 5, 1, 0},
  {5, 6, 2, 1},
  {7, 4, 0, 3}
};

GLfloat v[8][3] = {
    {-1, -1,  1},
    {-1, -1, -1},
    {-1,  1, -1},
    {-1,  1,  1},
    { 1, -1,  1},
    { 1, -1, -1},
    { 1,  1, -1},
    { 1,  1,  1}
};


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
  

    for (int i = 0; i < 6; i++) {
        glBegin(GL_QUADS);
        glNormal3fv(&n[i][0]);
        glVertex3fv(&v[faces[i][0]][0]);
        glVertex3fv(&v[faces[i][1]][0]);
        glVertex3fv(&v[faces[i][2]][0]);
        glVertex3fv(&v[faces[i][3]][0]);
        glEnd();
    }
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
