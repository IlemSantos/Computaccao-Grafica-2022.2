#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMouseEvent>
#include <QPoint>

class OpenGLWidget : public QOpenGLWidget, public QOpenGLFunctions
{
    Q_OBJECT

public:
    OpenGLWidget(QWidget *parent = nullptr);

public slots:
    void set_algorithm(int opt);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    int width;
    int height;
    QList<QPointF> points;
    int algorithm;

    void write_pixel(GLint x, GLint y);
    int binomial(int n, int i);
    float bernstein(int i, int n, float t);
    void DeCasteljau(QList<QPointF> points, int n, int i);
    QPointF Casteljau(QList<QPointF> points, int i, int j, int k, QList<QPointF> *esquerda, QList<QPointF> *direita);
};

#endif // OPENGLWIDGET_H
