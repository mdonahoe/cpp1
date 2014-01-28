
/* Modified by Matt Donahoe, 2014 */

/* Original Version Copyright (c) Mark J. Kilgard, 1997. */


#include "glheaders.h"
#include <cmath>
#include <vector>
#include "Box.h"

GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};  /* diffuse light. */
GLfloat light_position[] = {10.0, 10.0, 10.0, 0.0};  /* Infinite light location. */


static std::vector<Box> boxes;
static int t = 0;

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glRotatef(0.5,0,1,0);

    Vector p(4, sin(-0.05 * t++), 0);
    boxes[0].SetOrigin(p);
    boxes[0].SetRoll(t);
    boxes[0].draw();

    boxes[1].SetYaw(t);
    boxes[1].draw();

    for (auto it=boxes.begin(); it!=boxes.end(); it++){
        it->draw();
    }

    glutSwapBuffers();
    glutPostRedisplay();
}

void init() {
    /* Enable a single OpenGL light. */
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);

    /* Use depth buffering for hidden surface elimination. */
    glEnable(GL_DEPTH_TEST);

    /* Setup the view of the cube. */
    glMatrixMode(GL_PROJECTION);

    gluPerspective( /* field of view in degree */ 40.0,
    /* aspect ratio */ 1.0,
    /* Z near */ 1.0, /* Z far */ 100.0);

    glMatrixMode(GL_MODELVIEW);
    gluLookAt(0.0, 5.0, -20.0,  /* eye */
              0.0, 1.0, 0.0,   /* center */
              0.0, 1.0, 0.0);  /* up */

    Box obj = Box(3,1,1);
    boxes.push_back(obj);

    Box stand = Box(0.5,5,0.5);
    stand.SetOrigin(Vector(0,2.5,0));
    boxes.push_back(stand);

    Box floor = Box(5,0.333,5);
    boxes.push_back(floor);
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutCreateWindow("red 3D lighted cube");
  glutDisplayFunc(display);
  init();
  glutMainLoop();
  return 0;             /* ANSI C requires main to return int. */
}
