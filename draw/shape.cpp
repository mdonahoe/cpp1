#include "glheaders.h"
#include "shape.h"

GLfloat n[6][3] = {  /* Normals for the 6 faces of a cube. */
  {-1., 0.0, 0.0},
  {0.0, 1.0, 0.0},
  {-1.0, 0.0, 0.0},
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

GLfloat c[6][3] = { // colors for the 6 faces
    {1, 0, 0},
    {0, 1, 0},
    {0, 0, 1},
    {1, 1, 0},
    {0, 1, 1},
    {1, 0, 1},
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

void Cube(){
    for (int i = 0; i < 6; i++) {
        glBegin(GL_QUADS);
        glNormal3fv(&n[i][0]);
        glColor3fv(&c[i][0]);
        glVertex3fv(&v[faces[i][0]][0]);
        glVertex3fv(&v[faces[i][1]][0]);
        glVertex3fv(&v[faces[i][2]][0]);
        glVertex3fv(&v[faces[i][3]][0]);
        glEnd();
    }
};

void Prism(float length, float height, float width){
    glScalef(0.5 * length, 0.5 * height, 0.5 * width);
    Cube();
};
