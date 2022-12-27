#include "openglwidget.h"

OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget{parent}
{
}

void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    // glEnable(GL_DEPTH_TEST);
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
    glTranslatef(0.0f, 1.0f, 0.0);
}

void OpenGLWidget::paintGL()
{
    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT);

    QList<std::pair<int, int>> points;
    QList<std::pair<int, int>>::iterator it;

    switch (shapes)
    {
    case 0:
        algoritmoBresenhamCircunferencia(100, 100, 55);
        break;
    case 1:
        points.push_back(std::make_pair(100, 20));
        points.push_back(std::make_pair(100, 90));
        points.push_back(std::make_pair(210, 90));
        points.push_back(std::make_pair(210, 20));

        glPointSize(1.0);
        glColor3f(1.0f, 1.0f, 0.2f);
        glBegin(GL_LINE_LOOP);
            for (it = points.begin(); it != points.end(); ++it)
                glVertex2i((*it).first, (*it).second);
            glEnd();
        glFlush();
        break;
    case 2:
        points.push_back(std::make_pair(36, 105));
        points.push_back(std::make_pair(114, 177));
        points.push_back(std::make_pair(270, 99));
        points.push_back(std::make_pair(252, 51));
        points.push_back(std::make_pair(51, 24));
        points.push_back(std::make_pair(75, 66));

        glPointSize(1.0);
        glColor3f(1.0f, 1.0f, 0.2f);
        glBegin(GL_LINE_LOOP);
            for (it = points.begin(); it != points.end(); ++it)
                glVertex2i((*it).first, (*it).second);
            glEnd();
        glFlush();
        break;
    case 3:
        points.push_back(std::make_pair(18, 69));
        points.push_back(std::make_pair(102, 126));
        points.push_back(std::make_pair(189, 108));
        points.push_back(std::make_pair(201, 39));
        points.push_back(std::make_pair(99, 3));
        points.push_back(std::make_pair(87, 60));
        points.push_back(std::make_pair(129, 72));
        points.push_back(std::make_pair(114, 36));
        points.push_back(std::make_pair(36, 25));

        glPointSize(1.0);
        glColor3f(1.0f, 1.0f, 0.2f);
        glBegin(GL_LINE_LOOP);
            for (it = points.begin(); it != points.end(); ++it)
                glVertex2i((*it).first, (*it).second);
            glEnd();
        glFlush();
        break;
    default:
        break;
    }

    Qcolor cor = {0.2f, 0.2f, 0.2f};
    Qcolor novaCor = {1.0f, 0.0f, 0.0f};

    switch (algorithm)
    {
    case 0:
        algoritmoFloodFill(100, 100, cor, novaCor);
        break;
    case 1:
        algoritmoScanFill(points, novaCor);
    default:
        break;
    }
}

void OpenGLWidget::set_algorithm(int opt)
{
    algorithm = opt;
    update();
}

void OpenGLWidget::set_shapes(int opt)
{
    shapes = opt;
    update();
}

void OpenGLWidget::write_pixel(GLint x, GLint y)
{
    glPointSize(1.0);
    glColor3f(1.0f, 1.0f, 0.2f);
    glBegin(GL_POINTS);
        glVertex2i(x, y);
    glEnd();
    glFlush();
}

void OpenGLWidget::write_pixel(GLint x, GLint y, Qcolor cor)
{
    glPointSize(1.0);
    glColor3f(cor.r, cor.g, cor.b);
    glBegin(GL_POINTS);
        glVertex2i(x, y);
    glEnd();
    glFlush();
}

Qcolor OpenGLWidget::get_pixel(GLint x, GLint y)
{
    Qcolor cor;
    glReadPixels(x, y, 1, 1, GL_RGBA, GL_FLOAT, &cor);
    return cor;
}

void OpenGLWidget::algoritmoFloodFill(int x, int y, Qcolor cor, Qcolor newCor)
{
    Qcolor color = get_pixel(x, y);
    if (color.r == cor.r && color.g == cor.g && color.b == cor.b)
    {
        write_pixel(x, y, newCor);
        algoritmoFloodFill(x + 1, y, cor, newCor);
        algoritmoFloodFill(x, y + 1, cor, newCor);
        algoritmoFloodFill(x - 1, y, cor, newCor);
        algoritmoFloodFill(x, y - 1, cor, newCor);
    }
}

Side *OpenGLWidget::edgedetect(int x1, int y1, int x2, int y2)
{
    Side *side = new Side();

    side->y_min = std::min(y1, y2);
    side->y_max = std::max(y1, y2);
    side->y_min == y1 ? side->x_of_ymin = x1 : side->x_of_ymin = x2;
    side->m = (x2 - x1) / (float)(y2 - y1);

    return side;
}

void OpenGLWidget::algoritmoScanFill(QList<std::pair<int, int>> points, Qcolor cor)
{
    QList<std::pair<int, int>>::iterator it1;
    QList<std::pair<int, int>>::iterator it2;

    std::vector<Side *> table;
    std::vector<Side *>::iterator it;
    std::list<int> scan_line;

    switch (shapes)
    {
    case 0:
        algoritmoScanFillCircunferencia(100, 100, 55, cor);
        break;
    case 1:
        algoritmoScanFillRetangulo(points[0].first, points[0].second, points[2].first, points[2].second, cor);
        break;
    case 2:
    case 3:
        for (it1 = points.begin(), it2 = it1 + 1; it2 != points.end(); ++it1, ++it2)
            table.push_back(edgedetect((*it1).first, (*it1).second, (*it2).first, (*it2).second));

        it2 = points.begin();
        table.push_back(edgedetect((*it1).first, (*it1).second, (*it2).first, (*it2).second));

        float x;
        for (int y = 0, show = 0; y <= height / 2; y++)
        {
            scan_line.clear();
            for (it = table.begin(); it != table.end(); ++it)
            {
                if (y < (*it)->y_max && y >= (*it)->y_min)
                {
                    x = (*it)->m * (y - (*it)->y_min) + (*it)->x_of_ymin;
                    scan_line.push_back(round(x));
                }
            }

            scan_line.sort();
            // qDebug() << y << ':';
            // qDebug() << scan_line;

            for (int x = 0; x <= width / 2; ++x)
            {
                if (!scan_line.empty())
                {
                    if (x == scan_line.front())
                    {
                        ++show;
                        scan_line.pop_front();
                    }
                }
                if (show % 2 != 0)
                {
                    write_pixel(x, y, cor);
                    if (x == scan_line.front())
                    {
                        ++show;
                        scan_line.pop_front();
                    }
                }
            }
        }
        break;
    default:
        break;
    }
}

void OpenGLWidget::algoritmoScanFillCircunferencia(int xc, int yc, int r, Qcolor cor)
{
    r = r - 1;
    int y_min = yc - r;
    int y_max = yc + r;
    int x_min, x_max;
    for (int y = y_min; y <= y_max; y++)
    {
        x_min = round(xc - sqrt(pow(r, 2) - pow((y - yc), 2)));
        x_max = round(xc + sqrt(pow(r, 2) - pow((y - yc), 2)));
        for (int x = x_min; x <= x_max; x++)
        {
            write_pixel(x, y, cor);
        }
    }
}

void OpenGLWidget::algoritmoScanFillRetangulo(int x_min, int y_min, int x_max, int y_max, Qcolor cor)
{
    for (int y = y_min + 1; y < y_max; y++)
    {
        for (int x = x_min; x < x_max - 1; x++)
        {
            write_pixel(x, y, cor);
        }
    }
}

void OpenGLWidget::algoritmoBresenhamCircunferencia(int xc, int yc, int r)
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
