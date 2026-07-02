////////////////////////////////////////////////////////////////////          
// boxWithLookAt.cpp
//
// This program is box.cpp with the translation command replaced by
// an eqivalent viewing transformation.
//
// Sumanta Guha.
////////////////////////////////////////////////////////////////////

#include <iostream>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

using namespace std;

// Drawing routine.
void drawScene(void)
{
   glClear (GL_COLOR_BUFFER_BIT);
   glColor3f(0.0, 0.0, 0.0);
   glLoadIdentity(); 
   
   // Viewing transformation.
   gluLookAt(0.0, 0.0, 15.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); 
   // gluLookAt(0.0, 0.0, 15.0, 0.0, 0.0, 10.0, 0.0, 1.0, 0.0); 
   // gluLookAt(0.0, 0.0, 15.0, 0.0, 0.0, -10.0, 0.0, 1.0, 0.0); 
   // gluLookAt(0.0, 0.0, 15.0, 0.0, 0.0, 20.0, 0.0, 1.0, 0.<Paste>); 
   // gluLookAt(0.<Paste>, 0.<Paste>, 15.<Paste>, 0.<Paste>, 

   glPushMatrix();
   glTranslatef(0.0, 0.8, 0.0);
   glScalef(6.0, 0.3, 4.0);
   glutWireCube(1.0); // tampo
   glPopMatrix();

   glPushMatrix();
   glTranslatef(2.7, 0.0, 1.5);
   glScalef(0.4, 1.2, 0.4);
   glutWireCube(1.0); // perna frente-direita
   glPopMatrix();

   glPushMatrix();
   glTranslatef(-2.7, 0.0, 1.5);
   glScalef(0.4, 1.2, 0.4);
   glutWireCube(1.0); // perna frente-esquerda
   glPopMatrix();

   glPushMatrix();
   glTranslatef(2.7, 0.0, -1.5);
   glScalef(0.4, 1.2, 0.4);
   glutWireCube(1.0); // perna tras-direita
   glPopMatrix();

   glPushMatrix();
   glTranslatef(-2.7, 0.0, -1.5);
   glScalef(0.4, 1.2, 0.4);
   glutWireCube(1.0); // perna tras-esquerda
   glPopMatrix();
  
   

   glFlush();
}

// Initialization routine.
void setup(void) 
{
   glClearColor(1.0, 1.0, 1.0, 0.0);
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
   glViewport(0, 0, (GLsizei)w, (GLsizei)h); 
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 100.0);

   glMatrixMode(GL_MODELVIEW);
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
   switch(key) 
   {
      case 27:
         exit(0);
         break;
      default:
         break;
   }
}

// Main routine.
int main(int argc, char **argv) 
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
   glutInitWindowSize(500, 500);
   glutInitWindowPosition(100, 100); 
   glutCreateWindow("boxWithLookAt.cpp");
   setup(); 
   glutDisplayFunc(drawScene); 
   glutReshapeFunc(resize);  
   glutKeyboardFunc(keyInput);
   glutMainLoop(); 

   return 0;  
}
