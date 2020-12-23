#include <GL/freeglut.h>
#include <cmath>
#include <iostream>
#include "RigidBody//RigidBody.h"


using namespace std;
RigidBody rigidBody = RigidBody();
double const1 = sqrt(3)/6;
double const2 = sqrt(3)/3;
double const3 = sqrt(6)/12;
double h = sqrt(6)/3;
/*double rotate_y = 0;
double rotate_x = 0;*/

void Idle() {
    glutPostRedisplay();
}
void useRungeKutta(RigidBody &body, double h) {
    RigidBody k1, k2, k3, k4;

    k1 = body.f();
    k2 = (body.addRigidBody(k1.multipleScalar(h / 2))).f();
    k3 = (body.addRigidBody(k2.multipleScalar(h / 2))).f();
    k4 = (body.addRigidBody(k3.multipleScalar(h))).f();
    body = body.addRigidBody(k1.multipleScalar(1.0 / 6).addRigidBody(k2.multipleScalar(1.0 / 3)).addRigidBody(
            k3.multipleScalar(1.0 / 3)).addRigidBody(k4.multipleScalar(1.0 / 6)).multipleScalar(h));
}

// Функция обработки сообщений с клавиатуры
void Keyboard(unsigned char key, int x, int y)
{
#define ESCAPE '\033'
    if (key == ESCAPE)
        exit(0);
}
void drawTetraedr()
{
/*    glRotatef(rotate_x, 1.0, 0.0, 0.0);
    glRotatef(rotate_y, 0.0, 1.0, 0.0);*/
    glBegin(GL_TRIANGLES);

    //bottom triangle
    glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
    glVertex3f(-0.5f, -const1, -const3);//A
    glVertex3f( 0.5f, -const1, -const3);//C
    glVertex3f( 0.0f, const2 , -const3);//B

    //right side triangle
    glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
    glVertex3f(-0.5f, -const1, -const3);//A
    glVertex3f( 0.5f, -const1, -const3);//C
    glVertex3f( 0.0f,  0.0f, h -const3);//S

    //left side triangle
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glVertex3f( 0.0f,  0.0f, h -const3);//S
    glVertex3f(-0.5f, -const1, -const3);//A
    glVertex3f( 0.0f, const2 , -const3);//B

    //front triangle
    glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
    glVertex3f( 0.5f, -const1, -const3);//C
    glVertex3f( 0.0f,  0.0f, h-const3);//S
    glVertex3f( 0.0f, const2 , -const3);//B

    glEnd();
}

// управление курсором
/*void pressedSpecialKey(int key, int x, int y) {

    //  Правая стрелка - увеличение вращения на 5 градусов
    if (key == GLUT_KEY_RIGHT)
        rotate_y += 5;

        //  Левая стрелка - уменьшение вращения на 5 градусов
    else if (key == GLUT_KEY_LEFT)
        rotate_y -= 5;

    else if (key == GLUT_KEY_UP)
        rotate_x += 5;

    else if (key == GLUT_KEY_DOWN)
        rotate_x -= 5;

    //  Запрос обновления экрана
    glutPostRedisplay();

}*/

void Display()
{
    glViewport(0, 0, 1000, 1000);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1, 1, 500);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    useRungeKutta(rigidBody, 0.000001);
    glPushMatrix();
    glTranslated( 0, 0, -3);
    GLdouble rotationMatrixForOpenGL[16] = {rigidBody.R.matrix[0][0], rigidBody.R.matrix[1][0], rigidBody.R.matrix[2][0], 0, rigidBody.R.matrix[0][1], rigidBody.R.matrix[1][1], rigidBody.R.matrix[2][1], 0, rigidBody.R.matrix[0][2], rigidBody.R.matrix[1][2], rigidBody.R.matrix[2][2], 0, 0, 0, 0, 1};
    glMultMatrixd(rotationMatrixForOpenGL);
    drawTetraedr();
    glPopMatrix();
    glFlush();
    glutSwapBuffers();
}


int main(int argc,char** argv) {
    glutInit(&argc, argv); // начальная инициализация библиотеки GLUT
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA); // установка режима дисплея
    glutInitWindowSize(1000, 1000); // установка размера окна
    glutInitWindowPosition(100, 100); // установка положения окна на экране
    glutCreateWindow("Тетраэдр"); // запуск экранного окна
    glutDisplayFunc(Display);
//    glutSpecialFunc(pressedSpecialKey);
    glutIdleFunc(Idle);
    glEnable(GL_DEPTH_TEST);
    glutKeyboardFunc(Keyboard);
    glutMainLoop(); // вход в бесконечный цикл
    return 0;
}