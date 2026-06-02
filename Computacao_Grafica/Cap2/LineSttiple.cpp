/*
 *  lineStipple.cpp
 *
 *  This program draws a line with various stipples
 *
 *  Interaction:
 *  Press the space bar to cycle between stipples.
 *
 *  Sumanta Guha
 */

#include <iostream>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

using namespace std;

// Globals.
static int stippleID = 0; // Stipple ID.
static long font = (long)GLUT_BITMAP_8_BY_13; // Font selection.

// Routine to draw a bitmap character string.
void writeBitmapString(void *font, char *string)
{  
   char *c;

   for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}

// Drawing routine.
void drawScene(void)
{
   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(0.0, 0.0, 0.0);

   glLineWidth(5.0); // Aumenta a espessura ANTES de desenhar

   // Speficy the stipple pattern and write a label.
   glRasterPos3f(30.0, 40.0, 0.0);
   switch(stippleID) 
   {
      case 0: 
         glDisable(GL_LINE_STIPPLE);
		 writeBitmapString((void*)font, "No stipple");
         break;	
      case 1: 
		 glEnable(GL_LINE_STIPPLE);
		 glLineStipple(2, 0xAAAA); 
		 writeBitmapString((void*)font, "glLineStipple(2, 0xAAAA)");
         break;	  
      case 2:
		 glEnable(GL_LINE_STIPPLE);
		 glLineStipple(2, 0xCCCC);
		 writeBitmapString((void*)font, "glLineStipple(2, 0xCCCC)");
         break;
      case 3: 
		 glEnable(GL_LINE_STIPPLE);
		 glLineStipple(2, 0xF0F0); 
		 writeBitmapString((void*)font, "glLineStipple(2, 0xF0F0)");
         break;	  
      case 4:
		 glEnable(GL_LINE_STIPPLE);
		 glLineStipple(4, 0xAAAA);
		 writeBitmapString((void*)font, "glLineStipple(4, 0xAAAA)");
         break;
      default:
         break;
   }
   
   // Draw one straight line segment.
   glBegin(GL_LINES);
      glVertex3f(10.0, 50.0, 0.0);
	  glVertex3f(90.0, 50.0, 0.0);
   glEnd();

   glLineWidth(1.0); // Reset para espessura padrão
   glDisable(GL_LINE_STIPPLE); // Disable line stippling.

   glutSwapBuffers();
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
   glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 1.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
   switch(key) 
   {
      case ' ':
         if (stippleID < 4) stippleID++;
         else stippleID = 0;
         glutPostRedisplay();
         break;	  
      case 27:
         exit(0);
         break;
      default:
         break;
   }
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
   cout << "Interaction:" << endl;
   cout << "Press the space bar to cycle between stipples." << endl;
}

// Idle callback para forçar redesenho contínuo
void idle(void)
{
   glutPostRedisplay();
}

// Main routine.
int main(int argc, char **argv) 
{
   printInteraction();
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize(500, 500); 
   glutInitWindowPosition(100, 100);
   glutCreateWindow("lineStipple.cpp");
   setup();
   glutDisplayFunc(drawScene); 
   glutReshapeFunc(resize);  
   glutKeyboardFunc(keyInput);
   glutIdleFunc(idle);
   glutMainLoop();

   return 0;   
}