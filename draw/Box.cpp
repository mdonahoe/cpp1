#include "glheaders.h"

#include "Box.h"

GLfloat n[6][3] = {  /* Normals for the 6 faces of a cube. */
  {-1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {1.0, 0.0, 0.0},
  {0.0, -1.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, -1.0} };
GLint faces[6][4] = {  /* Vertex indices for the 6 faces of a cube. */
  {0, 1, 2, 3}, {3, 2, 6, 7}, {7, 6, 5, 4},
  {4, 5, 1, 0}, {5, 6, 2, 1}, {7, 4, 0, 3} };

GLfloat v[8][3] = {
    {-1, -1, 1},
    {-1, -1, -1},
    {-1, 1, -1},
    {-1, 1, 1},
    {1, -1, 1},
    {1, -1, -1},
    {1, 1, -1},
    {1, 1, 1}
};


Box::Box(float l, float w, float h): m_length(l),
                                     m_width(w),
                                     m_height(h),
                                     m_origin(0,0,0) {};

void Box::draw(){
    glPushMatrix();

    // the origin is the center of the box
    std::cout << "origin = " << m_origin << std::endl;
    glTranslatef(m_origin.x, m_origin.y, m_origin.z);
    // scale by the length width and height?
  

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
}
