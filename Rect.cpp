#include "Rect.h"

Rect::Rect()
{

}
void Rect::paint(QPainter &p)
{

    pen.setColor(shapecolor);
    pen.setWidth(shapewidth);
    pen.setStyle((Qt::PenStyle)shapestyle);
    p.setPen(pen);
    p.drawRect(start.x(),start.y(),end.x()-start.x(),end.y()-start.y());
}
