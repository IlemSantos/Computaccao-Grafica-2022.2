#include "openglwidget.h"

OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget{parent}
{
}

void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0.2f, 0.2f, 0.2f, 1.f);
    glEnable(GL_DEPTH_TEST);
}

void OpenGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-50.0, 50.0, -50.0, 50.0, 0.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void OpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    switch (algorithm)
    {
    case 0:
        algoritmoAnalitico(x_a, y_a, x_b, y_b);
        break;
    case 1:
        algoritmoDDA(x_a, y_a, x_b, y_b);
        break;
    case 2:
        algoritmoBresenham(x_a, y_a, x_b, y_b);
        break;
    default:
        break;
    }
}

void OpenGLWidget::set_algorithm(int opt)
{
    algorithm = opt;
    update();
}

void OpenGLWidget::set_points(int x1, int y1, int x2, int y2)
{
    x_a = x1;
    y_a = y1;
    x_b = x2;
    y_b = y2;
    update();
}

void OpenGLWidget::write_pixel(GLint x, GLint y)
{
    glPointSize(6);
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_POINTS);
        glVertex2i(x, y);
    glEnd();
    glFlush();
}

void OpenGLWidget::algoritmoAnalitico(int x1, int y1, int x2, int y2)
{
    if (x1 == x2) // reta vertical
    {
        bool show = y2 < y1;
        if (show)
        {
            y1 = -y1;
            y2 = -y2;
        }
        for (int y = y1; y <= y2; y++)
        {
            show ? write_pixel(x1, -y)
                 : write_pixel(x1, y);
        }
    }
    else
    {
        if (x2 < x1)
        {
            std::swap(x1, x2);
            std::swap(y1, y2);
        }
        float m = (float)(y2 - y1) / (float)(x2 - x1);
        int b = y2 - m * x2;
        for (int x = x1; x <= x2; x++)
        {
            float y = m * x + b;
            write_pixel(x, round(y));
        }
    }
}

void OpenGLWidget::algoritmoDDA(int x1, int y1, int x2, int y2)
{
    if (abs(x2 - x1) > abs(y2 - y1))
    {
        if (x2 < x1)
        {
            std::swap(x1, x2);
            std::swap(y1, y2);
        }
        float incremento = (float)(y2 - y1) / (float)(x2 - x1);
        float y = y1;
        for (int x = x1; x <= x2; x++)
        {
            write_pixel(x, round(y));
            y = y + incremento;
        }
    }
    else
    {
        bool show = y2 < y1;
        if (show)
        {
            y1 = -y1;
            y2 = -y2;
        }
        float incremento = (float)(x2 - x1) / (float)(y2 - y1);
        float x = x1;
        for (int y = y1; y <= y2; y++)
        {
            show ? write_pixel(round(x), -y)
                 : write_pixel(round(x), y);
            x = x + incremento;
        }
    }
}

void OpenGLWidget::algoritmoBresenham(int x1, int y1, int x2, int y2)
{
    if (x2 < x1)
    {
        std::swap(x1, x2);
        std::swap(y1, y2);
    }

    bool show = y2 < y1;
    if (show)
    {
        y1 = -y1;
        y2 = -y2;
    }

    if (abs(y2 - y1) > abs(x2 - x1))
    {
        std::swap(x1, y1);
        std::swap(x2, y2);
        int dy = y2 - y1;
        int dx = x2 - x1;
        int y = y1;
        int p = 2 * dy - dx;
        for (int x = x1; x <= x2; x++)
        {
            show ? write_pixel(y, -x)
                 : write_pixel(y, x);
            if (p >= 0)
            {
                y = y + 1;
                p = p + 2 * (dy - dx);
            }
            else
            {
                p = p + 2 * dy;
            }
        }
    }
    else
    {
        int dy = y2 - y1;
        int dx = x2 - x1;
        int y = y1;
        int p = 2 * dy - dx;
        for (int x = x1; x <= x2; x++)
        {
            show ? write_pixel(x, -y)
                 : write_pixel(x, y);
            if (p >= 0)
            {
                y = y + 1;
                p = p + 2 * (dy - dx);
            }
            else
            {
                p = p + 2 * dy;
            }
        }
    }
}
