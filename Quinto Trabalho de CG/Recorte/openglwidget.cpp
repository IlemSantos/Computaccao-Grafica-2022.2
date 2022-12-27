#include "openglwidget.h"

OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget{parent}
{
    window = {110, 440, 100, 300};
    clipping = 0;
    polygons = -1;
}

void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glEnable(GL_DEPTH_TEST);
}

void OpenGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, w, 0.0, h, 0.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void OpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    draw_viewport(window);

    QList<QPoint> polygon;

    switch (polygons)
    {
    case 0:
        // polygon.push_back(QPoint(530, 340));
        // polygon.push_back(QPoint(70, 200));
        // polygon.push_back(QPoint(530, 40));
        // polygon.push_back(QPoint(390, 200));
        // polygon.push_back(QPoint(530, 340));

        polygon.push_back(QPoint(150, 240));
        polygon.push_back(QPoint(150, 370));
        polygon.push_back(QPoint(420, 370));
        polygon.push_back(QPoint(420, 260));
        polygon.push_back(QPoint(370, 260));
        polygon.push_back(QPoint(370, 310));
        polygon.push_back(QPoint(200, 310));
        polygon.push_back(QPoint(200, 240));
        polygon.push_back(QPoint(150, 240));

        draw_polygon(polygon);
        break;
    case 1:
        polygon.push_back(QPoint(210, 150));
        polygon.push_back(QPoint(210, 370));
        polygon.push_back(QPoint(510, 150));
        polygon.push_back(QPoint(210, 150));

        draw_polygon(polygon);
        break;
    case 2:
        polygon.push_back(QPoint(160, 60));
        polygon.push_back(QPoint(160, 160));
        polygon.push_back(QPoint(200, 160));
        polygon.push_back(QPoint(200, 200));
        polygon.push_back(QPoint(300, 200));
        polygon.push_back(QPoint(300, 160));
        polygon.push_back(QPoint(340, 160));
        polygon.push_back(QPoint(340, 60));
        polygon.push_back(QPoint(300, 60));
        polygon.push_back(QPoint(300, 20));
        polygon.push_back(QPoint(200, 20));
        polygon.push_back(QPoint(200, 60));
        polygon.push_back(QPoint(160, 60));

        draw_polygon(polygon);
        break;
    case 3:
        polygon.push_back(QPoint(70, 160));
        polygon.push_back(QPoint(30, 260));
        polygon.push_back(QPoint(130, 340));
        polygon.push_back(QPoint(230, 260));
        polygon.push_back(QPoint(190, 160));
        polygon.push_back(QPoint(70, 160));

        draw_polygon(polygon);
        break;
    default:
        break;
    }

    if (clipping)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        draw_viewport(window);
        AlgoritmoSutherlandHodgman(polygon);
    }
}

void OpenGLWidget::set_clipping()
{
    clipping = 1;
    update();
}

void OpenGLWidget::set_polygon(int opt)
{
    polygons = opt;
    clipping = 0;
    update();
}

void OpenGLWidget::draw_viewport(viewport window)
{
    glPointSize(2.0);
    glColor3f(1.0f, 1.0f, 0);
    glBegin(GL_LINE_LOOP);
        glVertex2i(window.x_min, window.y_min);
        glVertex2i(window.x_min, window.y_max);
        glVertex2i(window.x_max, window.y_max);
        glVertex2i(window.x_max, window.y_min);
    glEnd();
    glFlush();
}

void OpenGLWidget::draw_polygon(QList<QPoint> polygon)
{
    glPointSize(1.0);
    glColor3f(1.0f, 1.0f, 0.2f);
    glBegin(GL_LINE_LOOP);
        for (auto it = polygon.begin(); it != polygon.end(); ++it)
            glVertex2i((*it).x(), (*it).y());
    glEnd();
    glFlush();
}

void OpenGLWidget::AlgoritmoSutherlandHodgman(QList<QPoint> polygon)
{
    QPoint p_t;
    float xt, yt, m;

    QList<QPoint> polygon_clip;

    // step 1: direita
    for (auto it = polygon.begin(); it != polygon.end() - 1; ++it)
    {
        m = ((*std::next(it, 1)).y() - (*it).y()) / (float)((*std::next(it, 1)).x() - (*it).x());

        // qDebug() << '(' << (*it).x() << ", " << (*it).y() << ')' << ", "
        //          << '(' << (*std::next(it, 1)).x() << ", " << (*std::next(it, 1)).y() << ')';

        if ((*it).x() < window.x_max && (*std::next(it, 1)).x() < window.x_max)
        {
            // qDebug() << "Caso 1: in -> in";
            // polygon_clip.push_back((*it));
            polygon_clip.push_back((*std::next(it, 1)));
        }
        else if ((*it).x() < window.x_max && (*std::next(it, 1)).x() > window.x_max)
        {
            // qDebug() << "Caso 2: in -> out";
            xt = window.x_max;
            yt = m * (window.x_max - (*it).x()) + (*it).y();
            p_t.setX(round(xt));
            p_t.setY(round(yt));
            polygon_clip.push_back(p_t);
        }
        else if ((*it).x() > window.x_max && (*std::next(it, 1)).x() > window.x_max)
        {
            // qDebug() << "Caso 3: out -> out";
        }
        else if ((*it).x() > window.x_max && (*std::next(it, 1)).x() < window.x_max)
        {
            // qDebug() << "Caso 4: out -> in";
            xt = window.x_max;
            yt = m * (window.x_max - (*it).x()) + (*it).y();
            p_t.setX(round(xt));
            p_t.setY(round(yt));
            polygon_clip.push_back(p_t);
            polygon_clip.push_back((*std::next(it, 1)));
        }
    }

    if (!polygon_clip.empty())
        polygon_clip.push_back(polygon_clip.front());

    polygon = polygon_clip;
    polygon_clip.clear();

    // step 2: esquerda
    for (auto it = polygon.begin(); it != polygon.end() - 1; ++it)
    {
        m = ((*std::next(it, 1)).y() - (*it).y()) / (float)((*std::next(it, 1)).x() - (*it).x());

        // qDebug() << '(' << (*it).x() << ", " << (*it).y() << ')' << ", "
        //          << '(' << (*std::next(it, 1)).x() << ", " << (*std::next(it, 1)).y() << ')';

        if ((*it).x() > window.x_min && (*std::next(it, 1)).x() > window.x_min)
        {
            // qDebug() << "Caso 1: in -> in";
            // polygon_clip.push_back((*it));
            polygon_clip.push_back((*std::next(it, 1)));
        }
        else if ((*it).x() > window.x_min && (*std::next(it, 1)).x() < window.x_min)
        {
            // qDebug() << "Caso 2: in -> out";
            xt = window.x_min;
            yt = m * (window.x_min - (*it).x()) + (*it).y();
            p_t.setX(round(xt));
            p_t.setY(round(yt));
            polygon_clip.push_back(p_t);
        }
        else if ((*it).x() < window.x_min && (*std::next(it, 1)).x() < window.x_min)
        {
            // qDebug() << "Caso 3: out -> out";
        }
        else if ((*it).x() < window.x_min && (*std::next(it, 1)).x() > window.x_min)
        {
            // qDebug() << "Caso 4: out -> in";
            xt = window.x_min;
            yt = m * (window.x_min - (*it).x()) + (*it).y();
            p_t.setX(round(xt));
            p_t.setY(round(yt));
            polygon_clip.push_back(p_t);
            polygon_clip.push_back((*std::next(it, 1)));
        }
    }

    if (!polygon_clip.empty())
        polygon_clip.push_back(polygon_clip.front());

    polygon = polygon_clip;
    polygon_clip.clear();

    // step 3: top
    for (auto it = polygon.begin(); it != polygon.end() - 1; ++it)
    {
        m = ((*std::next(it, 1)).y() - (*it).y()) / (float)((*std::next(it, 1)).x() - (*it).x());

        // qDebug() << '(' << (*it).x() << ", " << (*it).y() << ')' << ", "
        //          << '(' << (*std::next(it, 1)).x() << ", " << (*std::next(it, 1)).y() << ')';

        if ((*it).y() < window.y_max && (*std::next(it, 1)).y() < window.y_max)
        {
            // qDebug() << "Caso 1: in -> in";
            // polygon_clip.push_back((*it));
            polygon_clip.push_back((*std::next(it, 1)));
        }
        else if ((*it).y() < window.y_max && (*std::next(it, 1)).y() > window.y_max)
        {
            // qDebug() << "Caso 2: in -> out";
            xt = (*it).x() + (1 / (float)m) * (window.y_max - (*it).y());
            yt = window.y_max;
            p_t.setX(round(xt));
            p_t.setY(round(yt));
            polygon_clip.push_back(p_t);
        }
        else if ((*it).y() > window.y_max && (*std::next(it, 1)).y() > window.y_max)
        {
            // qDebug() << "Caso 3: out -> out";
        }
        else if ((*it).y() > window.y_max && (*std::next(it, 1)).y() < window.y_max)
        {
            // qDebug() << "Caso 4: out -> in";
            xt = (*it).x() + (1 / (float)m) * (window.y_max - (*it).y());
            yt = window.y_max;
            p_t.setX(round(xt));
            p_t.setY(round(yt));
            polygon_clip.push_back(p_t);
            polygon_clip.push_back((*std::next(it, 1)));
        }
    }

    if (!polygon_clip.empty())
        polygon_clip.push_back(polygon_clip.front());

    polygon = polygon_clip;
    polygon_clip.clear();

    // step 4: botton
    for (auto it = polygon.begin(); it != polygon.end() - 1; ++it)
    {
        m = ((*std::next(it, 1)).y() - (*it).y()) / (float)((*std::next(it, 1)).x() - (*it).x());

        // qDebug() << '(' << (*it).x() << ", " << (*it).y() << ')' << ", "
        //          << '(' << (*std::next(it, 1)).x() << ", " << (*std::next(it, 1)).y() << ')';

        if ((*it).y() > window.y_min && (*std::next(it, 1)).y() > window.y_min)
        {
            // qDebug() << "Caso 1: in -> in";
            // polygon_clip.push_back((*it));
            polygon_clip.push_back((*std::next(it, 1)));
        }
        else if ((*it).y() > window.y_min && (*std::next(it, 1)).y() < window.y_min)
        {
            // qDebug() << "Caso 2: in -> out";
            xt = (*it).x() + (1 / (float)m) * (window.y_min - (*it).y());
            yt = window.y_min;
            p_t.setX(round(xt));
            p_t.setY(round(yt));
            polygon_clip.push_back(p_t);
        }
        else if ((*it).y() < window.y_min && (*std::next(it, 1)).y() < window.y_min)
        {
            // qDebug() << "Caso 3: out -> out";
        }
        else if ((*it).y() < window.y_min && (*std::next(it, 1)).y() > window.y_min)
        {
            // qDebug() << "Caso 4: out -> in";
            xt = (*it).x() + (1 / (float)m) * (window.y_min - (*it).y());
            yt = window.y_min;
            p_t.setX(round(xt));
            p_t.setY(round(yt));
            polygon_clip.push_back(p_t);
            polygon_clip.push_back((*std::next(it, 1)));
        }
    }

    // for (auto it = polygon_clip.begin(); it != polygon_clip.end(); ++it)
    //     qDebug() << '(' << (*it).x() << ", " << (*it).y() << ')';

    draw_polygon(polygon_clip);
}
