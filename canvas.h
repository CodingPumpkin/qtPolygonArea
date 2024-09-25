#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include "vector"
#include <cmath>

class Canvas : public QWidget
{
    Q_OBJECT
public:
    explicit Canvas(QWidget *parent = nullptr);
    ~Canvas();
    std::vector<QPoint> points;
    std::vector<QPoint> polygonPoints;
    void drawMyPolygon();
    double getArea();
public slots:
    void clearImage();
signals:
    void newPointCreated();
protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *e);
private:
    void calculatePolygon();
    QImage image;
    QPainter *painter;
    void calculateArea();
    double area;
};

#endif // CANVAS_H
