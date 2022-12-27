#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QPoint>

class viewport
{
public:
    GLint x_min;
    GLint x_max;
    GLint y_min;
    GLint y_max;
};

class OpenGLWidget : public QOpenGLWidget, public QOpenGLFunctions
{
    Q_OBJECT

public:
    OpenGLWidget(QWidget *parent = nullptr);

public slots:
    void set_polygon(int opt);
    void set_clipping();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    viewport window;
    int clipping;
    int polygons;

    void draw_viewport(viewport window);
    void draw_polygon(QList<QPoint> polygon);
    void AlgoritmoSutherlandHodgman(QList<QPoint> polygon);
};

#endif // OPENGLWIDGET_H
