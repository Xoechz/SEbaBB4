/*---------------------------------------------------------------------------
 * Title: Computer Graphics Lab 2 - Meshes and Transformations
 * Author: Christoph Anthes
 * Version: 1.0 (SS22)
 * Time to complete: 90 minutes
 * Additional material: slides, course notes
 *-------------------------------------------------------------------------*/
#include "GL/freeglut.h"

int windowid; // the identifier of the GLUT window

GLfloat matrot[][4] = {          // a rotation matrix
  { 0.707f, 0.707f, 0.0f, 0.0f}, // it performs a rotation around z
  {-0.707f, 0.707f, 0.0f, 0.0f}, // in 45 degrees
  { 0.0f,   0.0f,   1.0f, 0.0f},
  { 0.0f,   0.0f,   0.0f, 1.0f}
};

GLfloat mattrans[][4] = {        // a translation matrix
  { 1.0f, 0.0f,  0.0f, 0.0f},    // it performs a translation along the
  { 0.0f, 1.0f,  0.0f, 0.0f},    // x-axis of 0.5 units and along
  { 0.0f, 0.0f,  1.0f, 0.0f},    // the z-axis of -1.5 units
  { 0.5f, 0.0f, -1.5f, 1.0f}
};

// Navigation variables - required for TASK 5
GLfloat navX = 0.0f;
GLfloat navZ = 5.0f;

// Angle for cube rotation - required for TASK 6
GLfloat angleCube = 0.0f;        //angle for cube1

// Camera motion variables - required for HOMEOWRK HELPER
GLdouble angle = 0.0f;          // angle of rotation for the camera direction
GLdouble lx = 0.0f, lz = -1.0f; // actual vector representing the camera's
// direction
GLdouble x = 0.0f, z = 5.0f;    // XZ position of the camera

/* This is the keyboard function which is used to react on keyboard input.
   It has to be registered as a callback in glutKeyboardFunc. Once a key is
   pressed it will be invoked and the keycode as well as the current mouse
   coordinates relative to the window origin are passed.
   It acts on our FPS controls 'WASD' and the escape key. A simple output
   to the keypress is printed in the console in case of 'WASD'. In case of
   ESC the window is destroyed and the application is terminated. */
void keyboard(unsigned char key, int xcoor, int ycoor)
{
    switch (key)
    {
    case 'a':
        break;
    case 'd':
        break;
    case 'w':
        break;
    case 's':
        break;
    case 27: // escape key
        glutDestroyWindow(windowid);
        exit(0);
        break;
    }
    glutPostRedisplay();
}

/* This function should be called when the window is resized. It has to be
   registered as a callback in glutReshapeFunc. The function sets up the
   correct perspective projection. Don't worry about it we will not go into
   detail but we need it for correct perspective 3D rendering. */
void reshapeFunc(int xwidth, int yheight)
{
    if (yheight == 0 || xwidth == 0) return;  // Nothing is visible, return

    glMatrixMode(GL_PROJECTION); // Set a new projection matrix
    glLoadIdentity();
    // Angle of view: 40 degrees
    // Near clipping plane distance: 0.5
    // Far clipping plane distance: 20.0
    gluPerspective(40.0f, (GLdouble)xwidth / (GLdouble)yheight, 0.5f, 20.0f);
    glViewport(0, 0, xwidth, yheight);  // Use the whole window for rendering
}

/* This is our first display function it will be used for drawing a 2D
   triangle. The background is set to black and cleared, the current drawing
   colour is set and the vertices of the triangle are defined. At the end the
   buffers are flipped. */
void renderPrimitives(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // set background colour to black 
    glClear(GL_COLOR_BUFFER_BIT);         // clear the colour buffer

    glBegin(GL_TRIANGLES);              // drawing using triangles
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);     // top
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 0.0f);   // bottom left
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 0.0f);    // bottom right
    glEnd();                            // finished drawing the triangle

    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex2f(0.8f, 0.8f);
    glVertex2f(0.7f, 0.6f);
    glVertex2f(0.6f, 0.7f);
    glVertex2f(0.6f, 0.6f);
    glVertex2f(0.8f, 0.6f);
    glVertex2f(0.9f, 0.7f);
    glEnd();
    glutSwapBuffers();
}

/* This function will be used for composited objects and will be called from a
   display function. */
void drawObject(void)
{ // TASK 4

}

/* This function will replace the previous display function and will be used
   for scene setup. */
void render3DScene(void)
{
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -1.5f);
    glRotatef(45, 0.5f, 0.5f, 0.0f);

    glColor3f(1.0f, 0.0f, 0.0f);
    glutSolidSphere(0.1f, 10, 10);

    glColor3f(0.0f, 0.0f, 1.0f);
    glutSolidTorus(0.2f, 0.4f, 20, 20);

    glColor3f(0.0f, 1.0f, 0.0f);
    glutSolidCube(0.5f);

    glutSwapBuffers();
}

/* This function will replace the previous display function and will be used
   for rendering a cube and playing with transformations. */
void renderCube(void)
{

}

/* This function will registered as a callback with glutIdleFunc. Here it will
   be constantly called and perform updates to realise an animation. */
void idleFunc(void)
{ // TASK 6

}

void drawTea(void)
{
    glColor3f(1.0f, 1.0f, 1.0f);
    glutSolidTeacup(0.4f);

    glPushMatrix();
    glRotatef(-90, 1.0f, 0.8f, 0.0f);
    glColor3f(0.5f, 0.5f, 0.5f);
    glutSolidTeaspoon(0.4f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.5f, 0.04f, 0.0f);
    glRotatef(135, 0.0f, 1.0f, 0.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    glutSolidTeapot(0.2f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.3f, -0.04f, 0.3f);
    glRotatef(90, 1.0f, 0.0f, 0.0f);
    glColor3f(1.0f, 0.5f, 0.5f);
    glutSolidTorus(0.05f, 0.1f, 30, 30);
    glPopMatrix();
}

void renderTea(void)
{

    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    glTranslatef(-0.2f, -0.3f, -1.5f);
    drawTea();
    glTranslatef(0.4f, 0.6f, 0.0f);
    glRotatef(45, 1.0f, 0.0f, 0.0f);
    drawTea();

    glutSwapBuffers();
}

/* This is our main method which will perform the setup of our first OpenGL
   window. The command line parameters will be passed but not used in the
   context of our application. Callbacks have been registered already and
   are prepared for future use during the lab. */
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(500, 500); // initial position of the window
    glutInitWindowSize(1200, 600); // initial size of the window
    windowid = glutCreateWindow("Our Second OpenGL Window"); // create window

    // register callbacks
    glutKeyboardFunc(keyboard);
    //glutDisplayFunc(renderPrimitives); // Part 1 - we simply render primitives
   // glutDisplayFunc(render3DScene);  // Part 2 - we start with 3D scene setup
    glutDisplayFunc(renderTea);
    glutReshapeFunc(reshapeFunc);    // Part 2 - keep reshape for all 3D parts
    //glutDisplayFunc(renderCube);     // Part 3 - we play with transformations 
    //glutIdleFunc(idleFunc);          // Part 4 - we perform basic animation 
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_DEPTH_TEST);

    glutMainLoop(); // start the main loop of GLUT
    return 0;
}