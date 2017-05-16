#include "glwidget.h"
//#include <GL/glut.h>
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
    glRotatef(rot, 0.0f, 1.0f, 0.0f);
    glBegin(GL_TRIANGLES);
        glColor3f(1,0,0);
        glVertex3f(0.0, 1.0, 0.0);

        glColor3f(0,1,0);
        glVertex3f(1.0, -1.0, 0.0);

        glColor3f(0,0,1);
        glVertex3f(-1.0, -1.0, 0.0);
    glEnd();
    glPopMatrix();
    glColor3f(1, 1, 0);
    for (int x = -50;x < 50;x++) {
        glBegin(GL_LINE_LOOP);
        glVertex3f(x, -1, -50);
        glVertex3f(x, -1, 50);
        glEnd();
    }
    for (int z = -50;z < 50;z++) {
        glBegin(GL_LINE_LOOP);
        glVertex3f(-50, -1, z);
        glVertex3f(50, -1, z);
        glEnd();
    }
}

void GLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65, (float)rect().right() / (float)rect().bottom(), 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

void GLWidget::keyPressEvent(QKeyEvent *e)
{
    float rad;
    switch (e->key()) {
    case Qt::Key_W:
        rad = (yrot + 90) * 3.141592 / 180;
        z += speed * sin(rad);
        x += speed * cos(rad);
        break;
    case Qt::Key_S:
        rad = (yrot + 90) * 3.141592 / 180;
        z -= speed * sin(rad);
        x -= speed * cos(rad);
        break;
    case Qt::Key_A:
        rad = yrot * 3.141592 / 180;
        x += speed * cos(rad);
        z += speed * sin(rad);
        break;
    case Qt::Key_D:
        rad = yrot * 3.141592 / 180;
        x -= speed * cos(rad);
        z -= speed * sin(rad);
        break;
    case Qt::Key_Q:
        yrot -= 2;
        break;
    case Qt::Key_E:
        yrot += 2;
        break;
    }
}
