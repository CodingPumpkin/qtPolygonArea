#include "canvas.h"

Canvas::Canvas(QWidget *parent)
    : QWidget{parent}
{
    painter = new QPainter(this);
    area = 0.0;
}

Canvas::~Canvas()
{
    delete painter;
}

void Canvas::paintEvent(QPaintEvent *event)
{
    painter->begin(this);
    for (auto& point : points)
    {
        painter->drawEllipse(point, 5, 5);
    }
    if (!polygonPoints.empty())
    {
        QPolygon poly;
        for (auto& point : polygonPoints)
        {
            poly << point;
        }
        painter->drawPolygon(poly);
    }
    painter->end();
    event->accept();
}
void Canvas::mousePressEvent(QMouseEvent *e)
{
    points.push_back(QPoint(e->x(), e->y()));
    emit newPointCreated();
    update();
}
void Canvas::clearImage()
{
    points.clear();
}
int orientation(QPoint p, QPoint q, QPoint r)
{
    int val = (q.y() - p.y()) * (r.x() - q.x()) -
              (q.x() - p.x()) * (r.y() - q.y());
    if (val == 0) return 0;  // collinear
    return (val > 0) ? 1 : 2; // clock or counterclock wise
}
void Canvas::calculatePolygon()
{
    int n = points.size();
    if (n >= 3)
    {
        int l = 0;
        for (int i = 1; i < n; i++)
            if (points[i].x() < points[l].x())
                l = i;
        int p = l, q = 0;
        do {
            polygonPoints.push_back(points[p]);
            q = (p + 1) % n;
            for (int i = 0; i < n; i++)
            {
                if (orientation(points[p], points[i], points[q]) == 2)
                    q = i;
            }
            p = q;
        } while (p != l);
    calculateArea();
    }
}
void Canvas::drawMyPolygon()
{
    calculatePolygon();
    update();
}
double Canvas::getArea()
{
    return area;
}
void Canvas::calculateArea()
{
    int n = points.size();
    area = 0.0;
    for (int i = 0; i < n-1; i++)
    {
        area += 1.0*(polygonPoints[i].x() * polygonPoints[i+1].y() -
                       polygonPoints[i].y() * polygonPoints[i+1].x());
    }
    area += 1.0*(polygonPoints[n-1].x() * polygonPoints[0].y() -
                      polygonPoints[n-1].y() * polygonPoints[0].x());
    area = fabs(area)*0.5;
}
