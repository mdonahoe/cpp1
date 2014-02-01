
/* Modified by Matt Donahoe, 2014 */

/* Original Version Copyright (c) Mark J. Kilgard, 1997. */


#include "glheaders.h"
#include <cmath>
#include <vector>
#include "RigidBody.h"
#include "Receiver.h"
#include "Quadrotor.h"
#include <iostream>

using namespace std;

GLfloat light_diffuse[] = {0.4, 0.4, 0.4, 1.0};  /* diffuse light. */
GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};  /* specular light. */
GLfloat light_position[] = {10.0, 10.0, 10.0, 0.0};  /* Infinite light location. */


static vector<RigidBody> bodies;
static Quadrotor quad = Quadrotor(1.0);
static Receiver rc = Receiver();
static float dt = 0.01;
static Vector3f eye(1.0,0.0,0.0);
static Vector3f position(0.0,4.0,4.0);

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (auto it=bodies.begin(); it!=bodies.end(); it++){
        it->update(dt);
        it->draw();
    }

    //quad.desire(position, eye);
    quad.manual(rc.GetControl());
    quad.update(dt);
    quad.draw();

    glutSwapBuffers();
    glutPostRedisplay();
}

void init() {
    // EnableDisable a single OpenGL light.

    // grey diffuse light
    glLightfv (GL_LIGHT0, GL_DIFFUSE, light_diffuse);

    // yellow specular light
    glLightfv (GL_LIGHT0, GL_SPECULAR, light_specular);

    // specify diffuse and specular material properties
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial (GL_FRONT, GL_DIFFUSE);
    glColorMaterial (GL_FRONT, GL_SPECULAR);

    // where it at?
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    //glEnable(GL_LIGHT0);
    //glEnable(GL_LIGHTING);

    /* Use depth buffering for hidden surface elimination. */
    glEnable(GL_DEPTH_TEST);

    /* Setup the view of the cube. */
    glMatrixMode(GL_PROJECTION);

    gluPerspective( /* field of view in degree */ 40.0,
    /* aspect ratio */ 1.0,
    /* Z near */ 1.0, /* Z far */ 100.0);

    glMatrixMode(GL_MODELVIEW);
    gluLookAt(0.0, 5.0, -20.0, /* eye */
              0.0, 1.0, 0.0,   /* center */
              0.0, 1.0, 0.0);  /* up */


    Matrix3f I;
    I << 1, 0, 0,
         0, 1, 0,
         0, 0, 1;

    RigidBody obj(2, I);
    obj.x << 3, 0, 0;
    bodies.push_back(obj);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("red 3D lighted cube");
    glutDisplayFunc(display);
    init();
    // also run the other thing in a thread. ugh!
    glutMainLoop();
    return 0;             /* ANSI C requires main to return int. */
}
