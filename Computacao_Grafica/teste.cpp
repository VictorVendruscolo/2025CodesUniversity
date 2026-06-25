///////////////////////////////////////////////////////////////////////////
// teste.cpp
//
// This program animates a ball rolling across a table, from one edge
// to the other, then stopping.
//
// Interaction:
// Press space to start/restart the animation.
// Press the up/down arrow keys to speed up/slow down animation.
//
///////////////////////////////////////////////////////////////////////////

#include <cstdlib>
#include <iostream>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

using namespace std;

// Globals.
static float t = 0.0; // Parameter (0 to 1) along the ball's path.
static float angle = 0.0; // Rolling rotation angle of the ball.
static int isAnimate = 0; // Animated?
static int animationPeriod = 100; // Time interval between frames.

// Drawing routine.
void drawScene(void)
{
   glClear(GL_COLOR_BUFFER_BIT);
   glLoadIdentity();

   // Place scene in frustum.
   glTranslatef(0.0, 0.0, -12.0);

   // Table.
   glColor3f(0.0, 0.0, 1.0);
   glPushMatrix();
   glScalef(1.0, 0.01, 0.75);
   glutWireCube(10.0);
   glPopMatrix();

   // Ball, rolling from right to left as t goes from 0 to 1.
   glColor3f(1.0, 0.0, 0.0);
   glTranslatef(5 * (1 - t) + t * -5, 2.0, 0.0);
   glRotatef(angle, 0.0, 0.0, 1.0);
   glutWireSphere(2.0, 10, 8);

   glutSwapBuffers();
}

// Timer function.
void animate(int value)
{
   if (isAnimate)
   {
      t += 0.01;
      angle += 5;
      if (t >= 1.0)
         isAnimate = 0;
   }
   glutTimerFunc(animationPeriod, animate, 1);
   glutPostRedisplay();
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
   switch (key)
   {
      case 27:
         exit(0);
         break;
      case ' ':
         if (isAnimate) isAnimate = 0;
         else
         {
            if (t >= 1.0)
            {
               t = 0.0;
               angle = 0.0;
            }
            isAnimate = 1;
         }
         glutPostRedisplay();
         break;
      default:
         break;
   }
}

// Callback routine for non-ASCII key entry.
void specialKeyInput(int key, int x, int y)
{
   if (key == GLUT_KEY_DOWN) animationPeriod += 5;
   if (key == GLUT_KEY_UP) if (animationPeriod > 5) animationPeriod -= 5;
   glutPostRedisplay();
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
   cout << "Interaction:" << endl;
   cout << "Press space to start/restart the animation." << endl
        << "Press the up/down arrow keys to speed up/slow down animation." << endl;
}

// Main routine.
int main(int argc, char **argv)
{
   printInteraction();
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize(500, 500);
   glutInitWindowPosition(100, 100);
   glutCreateWindow("teste.cpp");
   setup();
   glutDisplayFunc(drawScene);
   glutReshapeFunc(resize);
   glutKeyboardFunc(keyInput);
   glutSpecialFunc(specialKeyInput);
   glutTimerFunc(5, animate, 1);
   glutMainLoop();

   return 0;
}
