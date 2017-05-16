#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>

class GLWidget : public QGLWidget
{
private:
    float x;
    float y;
    float z;
    float yrot;
    float speed = 1.5;
    float rot = 0;
public:
    explicit GLWidget(QWidget *parent = 0);

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

    void keyPressEvent(QKeyEvent*e);
};

#endif // GLWIDGET_H
