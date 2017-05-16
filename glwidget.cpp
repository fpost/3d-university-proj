#include "glwidget.h"
#include <QDebug>
#include <GL/glut.h>
//#include "freeglut/include/GL/glut.h"
#include <QKeyEvent>
#include <GL/glu.h>
#include <QTimer>
#include <cmath>

GLWidget::GLWidget(QWidget* parent) :
    QGLWidget(parent)
{
    x = yrot = 0;
    y = 0;
    z = -3;
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(16.66666);
    setFocusPolicy(Qt::StrongFocus);
}

void GLWidget::initializeGL()
{
    glClearColor(0.3,0.3,0.3,1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
}

void GLWidget::paintGL()
{
    rot += 2;
    if (rot > 360) rot -= 360;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(yrot, 0.0f, 1.0f, 0.0f);
    glTranslatef(x, y, z);
    glPushMatrix();
    glBegin(GL_TRIANGLES);
    //Czworościan bez spodu
        glColor3f(1,0,0);
        glVertex3f(0.0, -1.0, 0.0);
        glVertex3f(0.5, -1.0, 0.0);
        glVertex3f(0.25, 0.5, 0.25);

        glColor3f(0,1,0);
        glVertex3f(0.5, -1.0, 0.0);
        glVertex3f(0.25, 0.5, 0.25);
        glVertex3f(0.25, -1.0, 0.5);

        glColor3f(0,0,1);
        glVertex3f(0.0, -1.0, 0.0);
        glVertex3f(0.25, 0.5, 0.25);
        glVertex3f(0.25, -1.0, 0.5);
    glEnd();
    glPopMatrix();
    glColor3f(0.75, 0.75, 0.75);

    for (int x = -50;x < 50;x++) {
        //Te są generowane w x
        glBegin(GL_LINE_LOOP);
        glVertex3f(x, -1, -50);
        glVertex3f(x, -1, 50);
        glEnd();
    }

    glBegin(GL_TRIANGLES);
        glColor3f(0.5, 0.5, 0);
        glVertex3f(-50, 10, 50);
        glVertex3f(50, -1, 50);
        glVertex3f(-50,-1,50);

        glColor3f(0.5, 0.65, 0.0);
        glVertex3f(50, 10, 50);
        glVertex3f(-50, 10, 50);
        glVertex3f(50,-1,50);

        glColor3f(0.5, 0.2, 0.2);
        glVertex3f(-50, 10, 50);
        glVertex3f(-50, -1, 50);
        glVertex3f(-50,-1, -50);

        glColor3f(0.5, 0.2, 0.25);
        glVertex3f(-50, 10, 50);
        glVertex3f(-50, 10, -50);
        glVertex3f(-50,-1, -50);

        glColor3f(0.5, 0.5, 0.5);
        glVertex3f(-50, 10, -50);
        glVertex3f(-50,-1, -50);
        glVertex3f(50, -1, -50);

        glColor3f(0.6, 0.6, 0.6);
        glVertex3f(-50, 10, -50);
        glVertex3f(50, 10, -50);
        glVertex3f(50, -1, -50);

        glColor3f(0.0, 0.0, 0.6);
        glVertex3f(50, -1, 50);
        glVertex3f(50, -1, -50);
        glVertex3f(50, 10, -50);

        glColor3f(0.0, 0.0, 0.3);
        glVertex3f(50, -1, 50);
        glVertex3f(50, 10, 50);
        glVertex3f(50, 10, -50);

    glEnd();
}

void GLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w / (float)h, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

void GLWidget::keyPressEvent(QKeyEvent *e)
{
    float rad;
    if(e->key() == Qt::Key_W)
    {
        rad = (yrot + 90) * 3.141592 / 180;
        z = z + speed * sin(rad);
        x = x + speed * cos(rad);
    }
    if(e->key() == Qt::Key_S)
    {
        rad = (yrot + 90) * 3.141592 / 180;
        z = z - speed * sin(rad);
        x = x - speed * cos(rad);
    }
    if(e->key() == Qt::Key_A)
    {
        rad = yrot * 3.141592 / 180;
        x = x + speed * cos(rad);
        z = z + speed * sin(rad);
    }
    if(e->key() == Qt::Key_D)
    {
        rad = yrot * 3.141592 / 180;
        x = x - speed * cos(rad);
        z = z - speed * sin(rad);
    }
    if(e->key() == Qt::Key_Q)
    {
        yrot = yrot - 5;
    }
    if(e->key() == Qt::Key_E)
    {
        yrot = yrot + 5;
    }

    if(e->key() == Qt::Key_Escape)
    {
        qDebug() << "Wcisnąłeś Esc, ale on jeszcze nic nie robi";
    }
}
