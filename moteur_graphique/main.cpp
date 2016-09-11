#include <iostream>
#include <GLUT/glut.h>


#include "Logger.hpp"

int WindowName;

void Reshape(int width, int height)
{
    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, float(width)/float(height), 0.1, 100);
    glMatrixMode(GL_MODELVIEW);
}

void Draw()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,0,-10,0,0,0,0,1,0);
    glBegin(GL_TRIANGLES);
    glVertex2i(0,1);
    glVertex2i(-1,0);
    glVertex2i(1,0);
    
    glEnd();
    glutSwapBuffers();
    
    glutPostRedisplay();
}

void InitGL()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
}

int main(int argc, char * argv[], char *envp[]) {
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(640,480);
    WindowName = glutCreateWindow("Ma première fenêtre OpenGL !");
    //glutFullScreen();
    
    glutReshapeFunc(Reshape);
    glutDisplayFunc(Draw);
    InitGL();
    
    glutMainLoop();
    
    return 0;
}
