///////////////////////////////////////////////////////////        
// Anel_de_Circulos.cpp
//
// This program draws 5 concentric circles using a display list.
// 
/////////////////////////////////////////////////////////

#include <cstdlib>
#include <cmath>
#include <iostream>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#define PI 3.14159265

using namespace std;

// Globals.
static unsigned int aCircle; // List index.

// Initialization routine.
void setup(void) 
{
   float t; // Angle parameter.

   aCircle = glGenLists(1); // Return a list index.

   // Begin create a display list.
   glNewList(aCircle, GL_COMPILE);

   // Draw a circle (unit circle in XY plane)
   glBegin(GL_LINE_LOOP);
   for(t = 0; t <= 2 * PI; t += PI/20.0) 
      glVertex3f(cos(t), sin(t), 0.0);
   glEnd();
   
   glEndList();
   // End create a display list.

   glClearColor(1.0, 1.0, 1.0, 0.0);  
}

// Initialization routine.
void drawScene(void)
{  
   glClear(GL_COLOR_BUFFER_BIT);

   // Array of colors for 5 circles
   float colors[5][3] = {
      {1.0, 0.0, 0.0},   // Red
      {0.0, 1.0, 0.0},   // Green
      {0.0, 0.0, 1.0},   // Blue
      {1.0, 1.0, 0.0},   // Yellow
      {1.0, 0.0, 1.0}    // Magenta
   };

   // Draw 5 concentric circles
   for(int i = 0; i < 5; i++)
   {
      float u = (i + 1) * 0.2; // scales: 0.2, 0.4, 0.6, 0.8, 1.0
      
      glColor3f(colors[i][0], colors[i][1], colors[i][2]);
      glPushMatrix();
      glScalef(u, u, 1.0);
      glCallList(aCircle); // Execute display list.
      glPopMatrix();
   }

   glFlush();
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
   glViewport(0, 0, (GLsizei)w, (GLsizei)h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-1.5, 1.5, -1.5, 1.5, -1.0, 1.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
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
   glutCreateWindow("Anel de Circulos");
   setup(); 
   glutDisplayFunc(drawScene); 
   glutReshapeFunc(resize);  
   glutKeyboardFunc(keyInput);
   glutMainLoop(); 

   return 0;  
}