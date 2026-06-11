#include <iostream>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/freeglut.h>
#endif

using namespace std;

void draw_wheel() {
    // Pneu maior: raio externo passou de 4.0 para 8.0
    glutWireTorus(1.5, 8.0, 15, 15);
}

void draw_bolt() {
    glutWireSphere(0.5, 8, 8);
}

void draw_car_body() {
    glPushMatrix();
    // Chassi levantado para 9.0 para acomodar a roda maior
    glTranslatef(0.0, 9.0, 0.0); 
    glScalef(100.0, 20.0, 50.0); 
    glutWireCube(1.0);
    glPopMatrix();
}

void draw_wheel_and_bolts() {
    long i;
    draw_wheel();
    for(i = 0; i < 5; i++) {
        glPushMatrix();
        glRotatef(72.0 * i, 0.0, 0.0, 1.0);
        // Distância mantida em 3.0. Como a roda tem 8.0, os parafusos ficam ao centro.
        glTranslatef(3.0, 0.0, 0.0);
        draw_bolt();
        glPopMatrix();
    }
}

void draw_body_and_wheel_and_bolts() {
    draw_car_body();

    glPushMatrix();
    glTranslatef(40.0, 0.0, 30.0); 
    draw_wheel_and_bolts();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(40.0, 0.0, -30.0); 
    draw_wheel_and_bolts();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-40.0, 0.0, 30.0); 
    draw_wheel_and_bolts();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-40.0, 0.0, -30.0); 
    draw_wheel_and_bolts();
    glPopMatrix();
}

void drawScene(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    glLoadIdentity();

    // Câmera afastada um pouco para focar no novo tamanho
    glTranslatef(0.0, 0.0, -120.0);
    glRotatef(25.0, 1.0, 1.0, 0.0); 

    draw_body_and_wheel_and_bolts();

    glFlush();
}

void setup(void) {
   glClearColor(1.0, 1.0, 1.0, 0.0);  
}

void resize(int w, int h) {
   glViewport(0, 0, (GLsizei)w, (GLsizei)h); 
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glFrustum(-35.0, 35.0, -35.0, 35.0, 35.0, 500.0);
   glMatrixMode(GL_MODELVIEW);
}

void keyInput(unsigned char key, int x, int y) {
   switch(key) {
      case 27:
         exit(0);
         break;
      default:
         break;
   }
}

int main(int argc, char **argv) {
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
   glutInitWindowSize(800, 600); 
   glutInitWindowPosition(100, 100); 
   glutCreateWindow("Carro Escala Original - Rodas Maiores");
   setup(); 
   glutDisplayFunc(drawScene); 
   glutReshapeFunc(resize);  
   glutKeyboardFunc(keyInput);
   glutMainLoop(); 

   return 0;  
}