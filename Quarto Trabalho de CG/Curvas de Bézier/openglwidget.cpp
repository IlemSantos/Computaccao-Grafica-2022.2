#include "openglwidget.h"

OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget{parent}
{
    algorithm = -1;
}

void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
}

void OpenGLWidget::resizeGL(int w, int h)
{
    width = w;
    height = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, w, 0.0, h, 0.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void OpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    if (points.empty())
        return;

    glPointSize(2.0);
    glColor3f(1.0f, 1.0f, 0);
    glBegin(GL_POINTS);
        for (auto it = points.begin(); it != points.end(); ++it)
            glVertex2i((*it).x(), (*it).y());
    glEnd();
    glFlush();

    float Bernstein, xt, yt;
    int n = points.length();
    switch (algorithm)
    {
    case 0:
        for (float t = 0.0; t <= 1.0; t += 0.001)
        {
            xt = 0;
            yt = 0;
            for (int i = 0; i < n; i++)
            {
                Bernstein = bernstein(i, n - 1, t);
                xt += Bernstein * points.at(i).x();
                yt += Bernstein * points.at(i).y();
            }
            write_pixel(round(xt), round(yt));
        }
        break;
    case 1:
        DeCasteljau(points, n - 1, 12);
        break;
    default:
        break;
    }
}

void OpenGLWidget::mousePressEvent(QMouseEvent *event)
{
    // QPoint point = event->pos();
    // point.setY(height - point.y());
    // points.push_back(point);
    // update();
}

void OpenGLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    QPoint point = event->pos();
    point.setY(height - point.y());
    points.push_back(point);
    update();
}

void OpenGLWidget::set_algorithm(int opt)
{
    algorithm = opt;
    update();
}

void OpenGLWidget::write_pixel(GLint x, GLint y)
{
    glPointSize(2.0);
    glColor3f(1.0f, 1.0f, 0);
    glBegin(GL_POINTS);
        glVertex2i(x, y);
    glEnd();
    glFlush();
}

int OpenGLWidget::binomial(int n, int i)
{
    int res = 1;

    if (i > n - i)
        i = n - i;

    for (int y = 0; y < i; ++y)
    {
        res *= (n - y);
        res /= (y + 1);
    }

    return res;
}

float OpenGLWidget::bernstein(int i, int n, float t)
{
    float Bernstein = binomial(n, i) * std::pow(t, i) * std::pow(1 - t, n - i);
    return Bernstein;
}

// qDebug() << "Esquerda:";
// for (auto it = left.begin(); it != left.end(); ++it)
//     qDebug() << '(' << (*it).x() << ", " << (*it).y() << ')';
// qDebug() << "Direita:";
// for (auto it = right.begin(); it != right.end(); ++it)
//     qDebug() << '(' << (*it).x() << ", " << (*it).y() << ')';

void OpenGLWidget::DeCasteljau(QList<QPointF> points, int n, int i)
{
    if (i <= 0)
    {
        return;
    }
    else
    {
        QPointF point;
        QList<QPointF> left, right;
        point = Casteljau(points, 0, n, n, &left, &right);
        write_pixel(round(point.x()), round(point.y()));

        DeCasteljau(left, n, i - 1);
        DeCasteljau(right, n, i - 1);
    }
}

QPointF OpenGLWidget::Casteljau(QList<QPointF> points, int i, int j, int k, QList<QPointF> *esquerda, QList<QPointF> *direita)
{
    if (j == 0)
    {
        if (i == 0)
            esquerda->push_back(points.at(i));

        if (i == k)
            direita->push_front(points.at(i));

        return (points.at(i));
    }

    QPointF a = Casteljau(points, i, j - 1, k, esquerda, direita);
    QPointF b = Casteljau(points, i + 1, j - 1, k, esquerda, direita);

    float xt = (a.x() + b.x()) / 2.0;
    float yt = (a.y() + b.y()) / 2.0;
    QPointF meio(xt, yt);

    if (i == 0)
        esquerda->push_back(meio);

    if (i + j == k)
        direita->push_front(meio);

    return meio;
}
