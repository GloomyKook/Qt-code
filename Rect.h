#ifndef RECT_H
#define RECT_H

#include"shape.h"
class Rect :public shape
{
public:
    Rect();
    void paint(QPainter &p);

};

#endif // RECT_H
