#include "polygon.h"
#include<cmath>
#include<vector>

polygon::polygon()
{

}

void polygon::paint(QPainter &p)
{
    pen.setColor(shapecolor);
    pen.setWidth(shapewidth);
    pen.setStyle((Qt::PenStyle)shapestyle);
    p.setPen(pen);
    double pi = 3.1415;
    double length;
    length = sqrt(pow((start.x()-end.x()),2)+pow((start.y()-end.y()),2));
    //qDebug()<<length;
    //qDebug()<<polygonSides;
    QPointF polygonPoints;
    std::vector<QPointF> points;
    for(int i=0; i<polygonSides; i++)
    {
       polygonPoints.setX(start.x()+(length*cos((i*360/polygonSides)*pi/180)));
       polygonPoints.setY(start.y()+(length*sin((i*360/polygonSides)*pi/180)));
       points.push_back(polygonPoints);
    }
    //qDebug()<<points;

    for(int i = 0; i<polygonSides-1; i++)
    {
       p.drawLine(points[i],points[i+1]);
    }
    p.drawLine(points.back(),points.front());
}
