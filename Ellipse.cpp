#include "Ellipse.h"

ellipse::ellipse()
{

}
void ellipse::paint(QPainter &p)
{
    pen.setColor(shapecolor);
    pen.setWidth(shapewidth);
    pen.setStyle((Qt::PenStyle)shapestyle);
    p.setPen(pen);
    p.drawEllipse(start,end.x()-start.x(),end.y()-start.y());
}
