#include "Line.h"

Line::Line()
{

}
void Line::paint(QPainter &p)
{


    pen.setColor(shapecolor);
    pen.setWidth(shapewidth);
    pen.setStyle((Qt::PenStyle)shapestyle);
    p.setPen(pen);
    p.drawLine(start,end);

}
