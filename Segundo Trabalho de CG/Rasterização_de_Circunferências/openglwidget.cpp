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
    glOrtho(-100.0, 100.0, -100.0, 100.0, 0.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void OpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    switch (algorithm)
    {
    case 0:
        algoritmoEquacaoParametrica(xc, yc, r);
        break;
    case 1:
        algoritmoIncrementalSimetria(xc, yc, r);
        break;
    case 2:
        algoritmoBresenham(xc, yc, r);
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

void OpenGLWidget::set_point(int x, int y)
{
    xc = x;
    yc = y;
    update();
}

void OpenGLWidget::set_radius(int radius)
{
    r = radius;
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

void OpenGLWidget::algoritmoEquacaoParametrica(int xc, int yc, int r)
{
    float x = xc + r;
    float y = yc;
    for (int t = 1; t <= 360; t++)
    {
        write_pixel(round(x), round(y));
        x = xc + r * cos((M_PI * t) / (float)180);
        y = yc + r * sin((M_PI * t) / (float)180);
    }
}

void OpenGLWidget::algoritmoIncrementalSimetria(int xc, int yc, int r)
{
    float teta = 1 / (float)r;
    float seno = sin(teta);
    float cosseno = cos(teta);
    float xi = r;
    float yi = 0;
    int x, y;
    float cp;
    while (xi >= yi)
    {
        x = round(xi);
        y = round(yi);
        write_pixel(x + xc, y + yc);
        write_pixel(y + xc, x + yc);
        write_pixel(-y + xc, x + yc);
        write_pixel(-x + xc, y + yc);
        write_pixel(-x + xc, -y + yc);
        write_pixel(-y + xc, -x + yc);
        write_pixel(y + xc, -x + yc);
        write_pixel(x + xc, -y + yc);
        cp = xi;
        xi = xi * cosseno - yi * seno;
        yi = yi * cosseno + cp * seno;
    }
}

void OpenGLWidget::algoritmoBresenham(int xc, int yc, int r)
{
    int x = 0;
    int y = r;
    int p = 1 - r;
    while (y >= x)
    {
        write_pixel(x + xc, y + yc);
        write_pixel(y + xc, x + yc);
        write_pixel(-y + xc, x + yc);
        write_pixel(-x + xc, y + yc);
        write_pixel(-x + xc, -y + yc);
        write_pixel(-y + xc, -x + yc);
        write_pixel(y + xc, -x + yc);
        write_pixel(x + xc, -y + yc);
        if (p >= 0)
        {
            y = y - 1;
            p = p + 2 * x - 2 * y + 5;
            x = x + 1;
        }
        else
        {
            p = p + 2 * x + 3;
            x = x + 1;
        }
    }
}
