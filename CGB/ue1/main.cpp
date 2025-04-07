#include<iostream>
#include<GL/freeglut.h>

int windowId;

void renderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'a':
        std::cout << "a x: " << x << " y: " << y << std::endl;
        break;
    case 27: //esc
        glutDestroyWindow(windowId);
        exit(0);
    case ' ':
        glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
        break;
    case 'g':
        glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
        break;
    }

    glutPostRedisplay();
}

void onMouseClick(int buttonId, int buttonState, int x, int y)
{
    if (buttonId == GLUT_MIDDLE_BUTTON && buttonState == GLUT_DOWN)
    {
        std::cout << "Middle mouse button x: " << x << " y: " << y << std::endl;
    }
    else if (buttonId == GLUT_RIGHT_BUTTON)
    {
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    }

    glutPostRedisplay();
}

void idle()
{
    glClearColor((rand() % 100) / 100.0f, (rand() % 100) / 100.0f, (rand() % 100) / 100.0f, 1.0f);
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowPosition(500, 500);
    glutInitWindowSize(800, 600);
    windowId = glutCreateWindow("OpenGL First Window");

    glutDisplayFunc(renderScene);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(onMouseClick);
    glutIdleFunc(idle);
    glutMainLoop();

    return 0;
}