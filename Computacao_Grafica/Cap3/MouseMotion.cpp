///////////////////////////////////////////////////////////////////////////////////         
// MouseMotion.cpp
// 
// This program allows the user to draw circles with 2 mouse clicks:
// First click sets the center, second click sets the radius.
// 
// Interaction:
// Left mouse click to set center, second left click to set radius, 
// right mouse click to exit.
// 
// Sumanta Guha (Modified).
/////////////////////////////////////////////////////////////////////////////////// 

#include <cstdlib>
#include <vector>
#include <iostream>
#include <cmath>
#include <ctime>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#define PI 3.14159265

// Use the STL extension of C++.
using namespace std;

// Globals.
static GLsizei width, height; // OpenGL window size.
static int clickCount = 0; // Count of clicks for current circle
static float centerX, centerY; // Center of circle being drawn
static float currentRed, currentGreen, currentBlue; // Color for current circle

// Circle class.
class Circle
{
public:
   Circle(float cx, float cy, float r, float r_col = 0.0, float g_col = 0.0, float b_col = 0.0)
   {
	  centerX = cx; centerY = cy; radius = r;
	  red = r_col; green = g_col; blue = b_col;
   }
   Circle(){};
   void drawCircle(void); // Function to draw a circle.
private:
   float centerX, centerY, radius;
   float red, green, blue;
};

// Function to draw a circle.
void Circle::drawCircle(void)
{  
   glColor3f(red, green, blue);
   glBegin(GL_LINE_LOOP);
   for(float t = 0; t <= 2 * PI; t += PI/20.0) 
      glVertex3f(centerX + radius * cos(t), centerY + radius * sin(t), 0.0);
   glEnd();   
}

// Function to calculate distance between two points
float distance(float x1, float y1, float x2, float y2)
{
   return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

// Vector of circles.
vector<Circle> circles;

// Iterator to traverse a Circle array.
vector<Circle>::iterator circlesIterator; 

// Current circle being drawn
Circle currentCircle(0, 0, 0);
float currentRadius = 0;

// Drawing routine.
void drawScene(void)
{
   glClear(GL_COLOR_BUFFER_BIT);

   // Loop through the circles array drawing each circle.
   circlesIterator = circles.begin();
   while(circlesIterator != circles.end() ) 
   {	   
	  circlesIterator->drawCircle();
	  circlesIterator++;
   }
 
   // Draw the circle being currently constructed
   if(clickCount == 1)
   {
	  Circle temp(centerX, centerY, currentRadius, currentRed, currentGreen, currentBlue);
	  temp.drawCircle();
	  // Draw center point as feedback
	  glColor3f(currentRed, currentGreen, currentBlue);
	  glPointSize(5.0);
	  glBegin(GL_POINTS);
	  glVertex3f(centerX, centerY, 0.0);
	  glEnd();
   }

   glFlush();
}

// Mouse callback routine.
void mouseControl(int button, int state, int x, int y)
{
   if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
   {
	  if(clickCount == 0)
	  {
		 // First click: set center and random color
		 centerX = x;
		 centerY = height - y;
		 currentRed = (float)rand() / RAND_MAX;
		 currentGreen = (float)rand() / RAND_MAX;
		 currentBlue = (float)rand() / RAND_MAX;
		 clickCount = 1;
	  }
	  else if(clickCount == 1)
	  {
		 // Second click: set radius and create circle
		 float radius = distance(centerX, centerY, (float)x, (float)(height - y));
		 circles.push_back(Circle(centerX, centerY, radius, currentRed, currentGreen, currentBlue));
		 clickCount = 0; // Reset for next circle
	  }
   }
   
   if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) exit(0);
   
   glutPostRedisplay();
}

// Mouse motion callback routine.
void mouseMotion(int x, int y)
{
   // Update the radius of the circle being drawn as the mouse moves after first click.
   if(clickCount == 1)
   {
	  currentRadius = distance(centerX, centerY, (float)x, (float)(height - y));
	  glutPostRedisplay();
   }
}

// Initialization routine.
void setup(void) 
{
   glClearColor(1.0, 1.0, 1.0, 0.0);
   srand(time(0)); // Initialize random seed
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
   glViewport (0, 0, (GLsizei)w, (GLsizei)h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   // Set viewing box dimensions equal to window dimensions.
   glOrtho(0.0, (float)w, 0.0, (float)h, -1.0, 1.0);

   // Pass the size of the OpenGL window to globals.
   width = w; 
   height = h; 

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
   switch (key) 
   {
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
   cout << "First left mouse click to set circle center," << endl 
        << "second left mouse click to set radius (move mouse to adjust radius)," << endl
        << "right mouse click to exit." << endl;
}

// Main routine.
int main(int argc, char **argv) 
{
   printInteraction();
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
   glutInitWindowSize(500, 500);
   glutInitWindowPosition(100, 100); 
   glutCreateWindow("Circle Drawer");
   setup(); 
   glutDisplayFunc(drawScene); 
   glutReshapeFunc(resize);  
   glutKeyboardFunc(keyInput);

   // Register the mouse callback function.
   glutMouseFunc(mouseControl); 

   // Register the mouse motion callback function.
   glutMotionFunc(mouseMotion);

   glutMainLoop(); 

   return 0;  
}