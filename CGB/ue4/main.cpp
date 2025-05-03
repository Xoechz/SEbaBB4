/*---------------------------------------------------------------------------
 * Title: Computer Graphics Lab 4 - Texture Mapping
 * Author: Christoph Anthes
 * Version: 1.0 (SS22)
 * Time to complete: 90 minutes
 * Additional material: slides, course notes
 *-------------------------------------------------------------------------*/
#include "GL/glew.h"      // to support GL_BGR
#include "GL/freeglut.h"
#include "stdio.h"

 // checkerboard texture dimensions
#define checkImageWidth 64
#define checkImageHeight 64

int windowid; // the identifier of the GLUT window

GLubyte checkImage[checkImageHeight][checkImageWidth][4]; // image data
GLuint texName; // internal texture name

// image data used for texturing
unsigned int imageWidth, imageHeight;  // dimensions in pixels
unsigned char* imageData;            // actual RGB data

char str[] = "marbles.bmp";      // filename to be loaded
char* filenameandpath = &str[0]; // pointer to filename and path to be loaded

/* This method is an adapted version of a common BMP loader. It takes path+
   filename as input parameters and tries to open and parse a BMP image. The
   actual image date will be stored in the byte array imageData. Metadata like
   width and height will be available. */
size_t loadBMP_custom(const char* imagepath)
{
    unsigned char header[54]; // each BMP file begins by a 54-bytes header
    unsigned int dataPos;     // position in the file where actual data begins
    unsigned int imageSize;   // = width * height * 3 (3 bytes, 1 per colour)
    FILE* file;
    file = fopen(imagepath, "rb");                   // open the file
    if (!file)
    {
        printf("Image could not be opened\n");
        return 0;
    }
    else if (fread(header, 1, 54, file) != 54)
    {     // if not 54 bytes read 
        printf("Not a correct BMP file\n");
        return 0;
    }
    else if (header[0] != 'B' || header[1] != 'M')
    { // if header is messed up
        printf("Not a correct BMP file\n");
        return 0;
    }

    // Read ints from the byte array
    dataPos = *(int*)&(header[0x0A]);
    imageSize = *(int*)&(header[0x22]);
    imageWidth = *(int*)&(header[0x12]);
    imageHeight = *(int*)&(header[0x16]);
    // Some BMP files are misformatted, we try to guess the missing information
    // 3 : one byte for each Red, Green and Blue component
    if (imageSize == 0)    imageSize = imageWidth * imageHeight * 3;
    if (dataPos == 0)      dataPos = 54; // the BMP header is done that way
    printf("imageSize: %i\n dataPos: %i\n", imageSize, dataPos);
    imageData = new unsigned char[imageSize]; // create a buffer
    size_t result = fread(imageData, 1, imageSize, file); // read data from the file into buffer

    fclose(file); // everything is in memory now, the file can be closed

    return result;
}

/* This function is used to create a checkerboard image and store it in
   checkImage */
void makeCheckImage(void)
{
    int i, j, c;

    for (i = 0; i < checkImageHeight; i++)
    {
        for (j = 0; j < checkImageWidth; j++)
        {
            c = ((((i & 0x8) == 0) ^ ((j & 0x8) == 0))) * 255;
            checkImage[i][j][0] = (GLubyte)c;    // red
            checkImage[i][j][1] = (GLubyte)c;    // green
            checkImage[i][j][2] = (GLubyte)c;    // blue
            checkImage[i][j][3] = (GLubyte)255;  // alpha
        }
    }
}

void initTextures(void)
{
    makeCheckImage();

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1, &texName);
    glBindTexture(GL_TEXTURE_2D, texName);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    loadBMP_custom("/home/elias/Repos/SEbaBB4/CGB/ue4/marbles64.bmp");

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_BGR, GL_UNSIGNED_BYTE, imageData);
}


/* The display method is used as a callback for rendering the scene. It
   will as usual be called either through glutPostRedisplay or when the
   window is updated through the callback functionality. */
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    glBindTexture(GL_TEXTURE_2D, texName);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0f, -1.0f, 0.0f);
    glTexCoord2f(0.0f, 2.0f); glVertex3f(-2.0f, 1.0f, 0.0f);
    glTexCoord2f(2.0f, 2.0f); glVertex3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(2.0f, 0.0f); glVertex3f(0.0f, -1.0f, 0.0f);

    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 0.0f);
    glTexCoord2f(0.0f, 2.0f); glVertex3f(1.0f, 1.0f, 0.0f);
    glTexCoord2f(2.0f, 2.0f); glVertex3f(2.41421f, 1.0f, -1.41421f);
    glTexCoord2f(2.0f, 0.0f); glVertex3f(2.41421f, -1.0f, -1.41421f);
    glEnd();

    glFlush();
    glDisable(GL_TEXTURE_2D);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, -4.5f);
    glutSwapBuffers();
}

/* The keyboard method will be used in this example  */
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 's':
        break;
    case 't':
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
void reshapeFunc(int x, int y)
{
    if (y == 0 || x == 0) return;  //Nothing is visible then, so return

    glMatrixMode(GL_PROJECTION); //Set a new projection matrix
    glLoadIdentity();
    //Angle of view: 40 degrees
    //Near clipping plane distance: 0.5
    //Far clipping plane distance: 20.0

    gluPerspective(40.0f, (GLdouble)x / (GLdouble)y, 0.5f, 40.0f);
    glViewport(0, 0, x, y);  //Use the whole window for rendering
}

/* This is our main method which will perform the setup of our fourth OpenGL
   window. The command line parameters will be passed but not used in the
   context of our application. Callbacks have been registered already and
   are prepared for future use during the lab. */
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(0, 1440); // initial position of the window
    glutInitWindowSize(1920, 1080);      // initial size of the window
    windowid = glutCreateWindow("Our Fourth OpenGL Window"); // create window

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_DEPTH_TEST);

    initTextures();

    // register callbacks
    glutDisplayFunc(display);
    glutReshapeFunc(reshapeFunc);
    glutKeyboardFunc(keyboard);

    glutFullScreen();      // GLUT Full Screen
    glutMainLoop();      // start the main loop of GLUT
    return 0;
}