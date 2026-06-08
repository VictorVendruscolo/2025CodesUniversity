/////////////////////////////////          
// box.cpp
//
// This program draws a wire box.
//
// Sumanta Guha.
/////////////////////////////////

#include <iostream>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/freeglut.h>
#endif

using namespace std;

// Drawing routine.
void drawScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -15.0);

    // Corpo (Box)
    glPushMatrix();
    glScalef(1.0, 2.0, 1.0);
    glutWireCube(5.0); 
    glPopMatrix();

    // Cabeça (Sphere)
    // Usamos o Push/Pop aqui também para a translação da cabeça não afetar as pernas
    glPushMatrix();
    glTranslatef(0.0, 7.0, 0.0);
    glutWireSphere(2.0, 10, 8); 
    glPopMatrix();

    // Perna Esquerda (Paralelepípedo)
    glPushMatrix();
    // Posiciona em X = -1.5 (esquerda), Y = -7.5 (abaixo do corpo)
    glTranslatef(-1.5, -7.5, 0.0); 
    // Escala para ficar com formato de perna (largura 1.5, altura 5.0, profundidade 1.5)
    glScalef(1.5, 5.0, 1.5); 
    glutWireCube(1.0); // Cubo base de tamanho 1.0
    glPopMatrix();

    // Perna Direita (Paralelepípedo)
    glPushMatrix();
    // Posiciona em X = 1.5 (direita), Y = -7.5 (abaixo do corpo)
    glTranslatef(1.5, -7.5, 0.0); 
    // Mesma escala da perna esquerda
    glScalef(1.5, 5.0, 1.5); 
    glutWireCube(1.0); // Cubo base de tamanho 1.0
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
   //glOrtho(-5.0, 5.0, -5.0, 5.0, 5.0, 100.0);
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
   glutCreateWindow("box.cpp");
   setup(); 
   glutDisplayFunc(drawScene); 
   glutReshapeFunc(resize);  
   glutKeyboardFunc(keyInput);
   glutMainLoop(); 

   return 0;  
}
