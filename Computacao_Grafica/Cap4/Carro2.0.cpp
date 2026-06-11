#include <iostream>
#include <cmath> // Necessário para sin() e cos()

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/freeglut.h>
#endif

using namespace std;

// Câmera e Física
float cameraAngleX = 25.0f, cameraAngleY = -25.0f, cameraZoom = -200.0f;
float steeringAngle = 0.0f, wheelRotation = 0.0f;
float carPosX = 0.0f, carPosZ = 0.0f, carAngle = 0.0f, carSpeed = 0.0f;
bool keys[256]; // Registra teclas pressionadas continuamente

void draw_wheel() {
    glutWireTorus(1.5, 8.0, 15, 15);
}

void draw_bolt() {
    glutWireSphere(0.5, 8, 8);
}

void draw_car_body() {
    glPushMatrix();
    glTranslatef(0.0, 9.0, 0.0); 
    glScalef(100.0, 15.0, 50.0); 
    glutWireCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-15.0, 21.0, 0.0); 
    glScalef(50.0, 10.0, 48.0); 
    glutWireCube(1.0);
    glPopMatrix();
}

void draw_wheel_and_bolts() {
    long i;
    draw_wheel();
    for(i = 0; i < 5; i++) {
        glPushMatrix();
        glRotatef(72.0 * i, 0.0, 0.0, 1.0);
        glTranslatef(3.0, 0.0, 0.0);
        draw_bolt();
        glPopMatrix();
    }
}

void draw_body_and_wheel_and_bolts() {
    draw_car_body();

    // Dianteira Direita
    glPushMatrix();
    glTranslatef(40.0, 0.0, 30.0); 
    glRotatef(steeringAngle, 0.0, 1.0, 0.0); // Esterço
    glRotatef(wheelRotation, 0.0, 0.0, 1.0); // Giro do pneu
    draw_wheel_and_bolts();
    glPopMatrix();

    // Dianteira Esquerda
    glPushMatrix();
    glTranslatef(40.0, 0.0, -30.0); 
    glRotatef(steeringAngle, 0.0, 1.0, 0.0); 
    glRotatef(wheelRotation, 0.0, 0.0, 1.0);
    draw_wheel_and_bolts();
    glPopMatrix();

    // Traseira Direita
    glPushMatrix();
    glTranslatef(-40.0, 0.0, 30.0); 
    glRotatef(-steeringAngle, 0.0, 1.0, 0.0); // 4-Wheel Steering
    glRotatef(wheelRotation, 0.0, 0.0, 1.0);
    draw_wheel_and_bolts();
    glPopMatrix();

    // Traseira Esquerda
    glPushMatrix();
    glTranslatef(-40.0, 0.0, -30.0); 
    glRotatef(-steeringAngle, 0.0, 1.0, 0.0); 
    glRotatef(wheelRotation, 0.0, 0.0, 1.0);
    draw_wheel_and_bolts();
    glPopMatrix();
}

// Pista simples (Grade infinita)
void draw_track() {
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_LINES);
    for(int i = -2000; i <= 2000; i += 50) {
        glVertex3f(i, -8.0f, -2000); 
        glVertex3f(i, -8.0f, 2000);
        glVertex3f(-2000, -8.0f, i); 
        glVertex3f(2000, -8.0f, i);
    }
    glEnd();
}

void drawScene(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    glLoadIdentity();

    // Câmera segue o carro e obedece ao zoom/rotação
    glTranslatef(0.0f, -20.0f, cameraZoom);
    glRotatef(cameraAngleX, 1.0, 0.0, 0.0); 
    glRotatef(cameraAngleY, 0.0, 1.0, 0.0);
    glTranslatef(-carPosX, 0.0f, -carPosZ); // Foco no carro

    draw_track();

    // Posiciona o carro no mundo
    glPushMatrix();
    glTranslatef(carPosX, 0.0f, carPosZ);
    glRotatef(carAngle, 0.0f, 1.0f, 0.0f);
    draw_body_and_wheel_and_bolts();
    glPopMatrix();

    glutSwapBuffers();
}

// Game Loop: 60 FPS e Física
void update(int value) {
    // Aceleração e Freio
    if (keys['w'] || keys['W']) carSpeed += 0.5f;
    else if (keys['s'] || keys['S']) carSpeed -= 0.5f;
    else carSpeed *= 0.95f; // Atrito/Freio motor

    // Limite de velocidade
    if (carSpeed > 15.0f) carSpeed = 15.0f;
    if (carSpeed < -10.0f) carSpeed = -10.0f;

    // Volante (retorna ao centro sozinho)
    if (keys['a'] || keys['A']) {
        steeringAngle += 4.0f;
        if (steeringAngle > 40.0f) steeringAngle = 40.0f;
    } else if (keys['d'] || keys['D']) {
        steeringAngle -= 4.0f;
        if (steeringAngle < -40.0f) steeringAngle = -40.0f;
    } else {
        steeringAngle *= 0.8f; 
    }

    // Calcula a nova rotação do carro com base no esterço e na velocidade
    carAngle += steeringAngle * (carSpeed * 0.003f);
    
    // Gira as rodas fisicamente
    wheelRotation -= carSpeed * 2.0f;

    // Move o carro na pista usando trigonometria
    float rad = carAngle * 3.14159f / 180.0f;
    carPosX += carSpeed * cos(rad);
    carPosZ -= carSpeed * sin(rad);

    glutPostRedisplay();
    glutTimerFunc(16, update, 0); // ~60 FPS
}

void setup(void) {
   glClearColor(1.0, 1.0, 1.0, 0.0);  
}

void resize(int w, int h) {
   glViewport(0, 0, (GLsizei)w, (GLsizei)h); 
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glFrustum(-35.0, 35.0, -35.0, 35.0, 35.0, 2000.0); // Visão estendida
   glMatrixMode(GL_MODELVIEW);
}

// Eventos de Teclado (Pressionar e Soltar)
void keyDown(unsigned char key, int x, int y) {
    keys[key] = true;
    if(key == 27) exit(0);
    if(key == '+') cameraZoom += 10.0f;
    if(key == '-') cameraZoom -= 10.0f;
}

void keyUp(unsigned char key, int x, int y) {
    keys[key] = false;
}

void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:  cameraAngleY -= 3.0f; break;
        case GLUT_KEY_RIGHT: cameraAngleY += 3.0f; break;
        case GLUT_KEY_UP:    cameraAngleX -= 3.0f; break;
        case GLUT_KEY_DOWN:  cameraAngleX += 3.0f; break;
    }
}

int main(int argc, char **argv) {
   for(int i=0; i<256; i++) keys[i] = false;

   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); 
   glutInitWindowSize(800, 600); 
   glutCreateWindow("Monster Truck GL - 60 FPS");
   
   setup(); 
   glutDisplayFunc(drawScene); 
   glutReshapeFunc(resize);  
   
   // Registra as funções de controle e o Game Loop
   glutKeyboardFunc(keyDown);       
   glutKeyboardUpFunc(keyUp);
   glutSpecialFunc(specialKeys);     
   glutTimerFunc(16, update, 0); 
   
   glutMainLoop(); 
   return 0;  
}