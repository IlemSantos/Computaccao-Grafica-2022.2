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
    void set_point(int x, int y);
    void set_radius(int radius);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    int xc, yc;
    int r;
    int algorithm;

    void write_pixel(GLint x, GLint y);
    void algoritmoEquacaoParametrica(int xc, int yc, int r);
    void algoritmoIncrementalSimetria(int xc, int yc, int r);
    void algoritmoBresenham(int xc, int yc, int r);
};

#endif // OPENGLWIDGET_H
