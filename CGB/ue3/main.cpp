/*---------------------------------------------------------------------------
 * Title: Computer Graphics Lab 3 - Lighting and Shading
 * Author: Christoph Anthes
 * Version: 1.0 (SS22)
 * Time to complete: 90 minutes
 * Additional material: slides, course notes
 *-------------------------------------------------------------------------*/
#include "GL/freeglut.h"
#include "math.h"
#include <iostream>

int windowid; // the identifier of the GLUT window

// Predefined material attributes to play with
GLfloat no_mat[] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat no_shininess = 0.0f;
GLfloat low_shininess = 5.0f;
GLfloat high_shininess = 100.0f;
GLfloat mat_emission[] = { 0.3f, 0.2f, 0.2f, 0.0f };
GLfloat mat_shininess[] = { 50.0 };
GLfloat mat_ambient_color[] = { 0.8f, 0.8f, 0.2f, 1.0f };
GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
GLfloat mat_diffuse[] = { 0.1f, 0.5f, 0.8f, 1.0f };

// Predefined lighting attributes to play with
float light_direction[] = { 1.0f, 1.0f, 1.0f, 0.0f };
GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
GLfloat light_diffuse[] = { 1.0f, 0.5f, 0.5f, 1.0f };
GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat attenuation = 0.0f;

// Used for spotlight rotation
GLfloat angle = 0.0f; // angle of rotation for the spotlight direction
GLfloat lx = 0.0f, lz = -1.0f; // actual vector components representing
// the spotlight direction

/* This method provides a very generic setup for fog in OpenGL. Parameters
   are set. The fog is enabled. */
void foggy()
{
    GLuint fogMode[] = { GL_EXP, GL_EXP2, GL_LINEAR }; //  types of fog
    GLuint fogfilter = 2;                              // which fog to use
    GLfloat fogColor[4] = { 0.5f, 0.5f, 0.5f, 1.0f };  // fog colour

    glFogi(GL_FOG_MODE, fogMode[fogfilter]);  // fog mode
    glFogfv(GL_FOG_COLOR, fogColor);          // set fog colour
    glFogf(GL_FOG_DENSITY, 0.35f);            // how dense will the fog be
    glHint(GL_FOG_HINT, GL_DONT_CARE);        // fog hint value
    glFogf(GL_FOG_START, 2.0f);               // fog start depth
    glFogf(GL_FOG_END, 4.0f);                 // fog end depth
    glEnable(GL_FOG);                         // enables GL_FOG
};

/* A method for constant rotation of the spotlight introduced in the lab.
   It has to be registered in the idle function to generate permanent
   updates. */
void rotateSpot(void)
{
    angle -= 0.005f;
    lx = sin(angle);
    lz = -cos(angle);
    GLfloat spot_direction[] = { lx, 0.0f, lz, 1.0f }; //rotate
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction);
    glutPostRedisplay();
}

/* The keyboard method will be used in this example to alter the direction of
   the directional light with the keys 1 to 3 and to change the attenuation
   of a light source by processing + and - keys. */
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case '1':
        light_direction[0] = -1.0f;
        light_direction[1] = 0.0f;
        light_direction[2] = 0.0f;
        light_direction[3] = 0.0f;
        break;
    case '2':
        light_direction[0] = 0.0f;
        light_direction[1] = 1.0f;
        light_direction[2] = 0.0f;
        light_direction[3] = 0.0f;
        break;
    case '3':
        light_direction[0] = 0.0f;
        light_direction[1] = 0.0f;
        light_direction[2] = 1.0f;
        light_direction[3] = 0.0f;
        break;
    case '0':
        light_direction[0] = 1.0f;
        light_direction[1] = 1.0f;
        light_direction[2] = 1.0f;
        light_direction[3] = 0.0f;
        break;
    case '+':
        glShadeModel(GL_FLAT);
        break;
    case '-':
        glShadeModel(GL_SMOOTH);
        break;
    case 27: // escape key
        glutDestroyWindow(windowid);
        exit(0);
        break;
    }

    std::cout << " l0: " << light_direction[0] << " l1: " << light_direction[1] << " l2: " << light_direction[2] << " l3: " << light_direction[3] << std::endl;
    glLightfv(GL_LIGHT0, GL_POSITION, light_direction);
    glutPostRedisplay();
}

/* This function should be called when the window is resized. It has to be
   registered as a callback in glutReshapeFunc. The function sets up the
   correct perspective projection. Don't worry about it we will not go into
   detail but we need it for correct perspective 3D rendering. */
void reshapeFunc(int xwidth, int yheight)
{
    if (yheight == 0 || xwidth == 0) return;  // nothing is visible, return

    glMatrixMode(GL_PROJECTION); // set a new projection matrix
    glLoadIdentity();
    // Angle of view: 40 degrees
    // Near clipping plane distance: 0.5
    // Far clipping plane distance: 20.0
    gluPerspective(40.0, (GLdouble)xwidth / (GLdouble)yheight, 0.5, 20.0);
    glViewport(0, 0, xwidth, yheight);  // use the whole window for rendering
}

void materialOne(void)
{
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
}

/* This method is used for light source initalisation, initially only the
   lighting is enabled and the depth test is used. Here our light sources
   will be placed. */
void initLightSources(void)
{
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    std::cout << " l0: " << light_direction[0] << " l1: " << light_direction[1] << " l2: " << light_direction[2] << " l3: " << light_direction[3] << std::endl;
    glLightfv(GL_LIGHT0, GL_POSITION, light_direction);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);

    return;

    GLfloat light_color[] = { 1.0f, 1.0f, 0.0f, 1.0f };
    GLfloat light_pos[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_color);
    glLightfv(GL_LIGHT1, GL_POSITION, light_pos);
    glEnable(GL_LIGHT1);

    GLfloat light_color2[] = { 0.3f, 0.3f, 0.9f, 1.0f };
    GLfloat light_pos2[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    GLfloat spot_direction[] = { 0.0f, 0.0f, -1.0f, 1.0f };

    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction);
    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 20);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, light_color2);
    glLightfv(GL_LIGHT2, GL_POSITION, light_pos2);
    glEnable(GL_LIGHT2);
}

/* This method is used for setting up the lighting in our OpenGL example
   The ambient light is set to a dark blue ambient light. The parameters
   are passed and the lighting itself is enabled. */
void lightingSetup(void)
{
    GLfloat lmodel_ambient[] = { 0.1f, 0.1f, 0.9f, 1.0f }; // dark blue

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_EMISSION);
}

/* The renderCube method is used for rendering an initial cube for colour
   appliance. It makes use of our known transformation helpers and
   clears before drawing the colour buffer and also the depth buffer.*/
void renderCube(void)
{
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glColor3f(0.5f, 0.0f, 0.0f);

    glPushMatrix();
    glLoadIdentity();
    glTranslatef(0.0f, 0.1f, -1.5f);
    glRotatef(45.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
    glutSolidCube(0.5f);
    glPopMatrix();

    glutSwapBuffers();
}

/* renderScene provides a setup of three cubes, which will be used for a
   variety of lighting experiments */
void renderScene(void)
{
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 0.0); // original black

    glPushMatrix();
    glLoadIdentity();
    glTranslatef(1.0f, 0.1f, -3.5f);
    glRotatef(45.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
    glutSolidSphere(0.5f, 30, 30);
    glPopMatrix();

    glPushMatrix();
    glLoadIdentity();
    glTranslatef(-1.0f, 0.1f, -2.5f);
    glRotatef(45.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
    glutSolidSphere(0.5f, 30, 30);
    glPopMatrix();

    glPushMatrix();
    glLoadIdentity();
    glTranslatef(0.0f, 0.5f, -3.0f);
    glRotatef(45.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
    glutSolidSphere(0.5f, 30, 30);
    glPopMatrix();

    glutSwapBuffers();
}

/* This is our main method which will perform the setup of our third OpenGL
   window. The command line parameters will be passed but not used in the
   context of our application. Callbacks have been registered already and
   are prepared for future use during the lab. */
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(0, 1440); // initial position of the window
    glutInitWindowSize(1920, 1080); // initial size of the window
    windowid = glutCreateWindow("Our Third OpenGL Window"); // create window
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // we use front and back sides 
    // of the polygons and have the full surfaces rendered

    // register callbacks
    // lightingSetup();
    glEnable(GL_NORMALIZE);
    initLightSources();
    materialOne();
    foggy();
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshapeFunc);
    //glutDisplayFunc(renderCube);
    glutDisplayFunc(renderScene);
    glutIdleFunc(rotateSpot);

    glutMainLoop(); // start the main loop of GLUT
    return 0;
}