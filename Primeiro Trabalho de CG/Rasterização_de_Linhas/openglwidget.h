#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class OpenGLWidget : public QOpenGLWidget, public QOpenGLFunctions
{
    Q_OBJECT

public:
    OpenGLWidget(QWidget *parent = nullptr);

public slots:
    void set_algorithm(int opt);
    void set_points(int x1, int y1, int x2, int y2);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    int x_a, y_a;
    int x_b, y_b;
    int algorithm;

    void write_pixel(GLint x, GLint y);
    void algoritmoAnalitico(int x1, int y1, int x2, int y2);
    void algoritmoDDA(int x1, int y1, int x2, int y2);
    void algoritmoBresenham(int x1, int y1, int x2, int y2);
};

#endif // OPENGLWIDGET_H
