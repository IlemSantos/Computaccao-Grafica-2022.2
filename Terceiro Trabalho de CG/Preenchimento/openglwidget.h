#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <vector>

class Qcolor
{
public:
    GLfloat r;
    GLfloat g;
    GLfloat b;
};

class Side
{
public:
    int y_min;
    int y_max;
    int x_of_ymin;
    float m;
};

class OpenGLWidget : public QOpenGLWidget, public QOpenGLFunctions
{
    Q_OBJECT

public:
    OpenGLWidget(QWidget *parent = nullptr);

public slots:
    void set_algorithm(int opt);
    void set_shapes(int opt);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    int width;
    int height;
    int shapes = -1;
    int algorithm = -1;

    void write_pixel(GLint x, GLint y);
    void write_pixel(GLint x, GLint y, Qcolor cor);
    Qcolor get_pixel(GLint x, GLint y);
    void algoritmoFloodFill(int x, int y, Qcolor cor, Qcolor newCor);
    Side *edgedetect(int x1, int y1, int x2, int y2);
    void algoritmoScanFill(QList<std::pair<int, int>> points, Qcolor cor);
    void algoritmoScanFillCircunferencia(int xc, int yc, int r, Qcolor cor);
    void algoritmoScanFillRetangulo(int x_min, int y_min, int x_max, int y_max, Qcolor cor);
    void algoritmoBresenhamCircunferencia(int xc, int yc, int r);
};

#endif // OPENGLWIDGET_H
