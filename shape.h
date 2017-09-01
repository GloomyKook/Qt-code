#ifndef SHAPE_H
#define SHAPE_H
#include<QtGui>

class shape
{
public:
    enum code{None,line,reck,ellipse,polygon};
    shape();
    void virtual paint(QPainter &p) = 0;
    void  sideNum(int );

    void setstrat(QPoint s);
    void setend(QPoint e);   
    void setshapewidth(int);
    void setshapecolor(QColor);
    void setshapestyle(int);
    void setshape(shape::code);

    shape::code getShape();
    QPoint startpoint();
    QPoint endpoint();
    QJsonObject setjson();
    int getsideNum();
    int getwidth();
    int getStyle();
    QColor getColor();

protected:
    QPoint start;
    QPoint end;
    int shapestyle;
    int shapewidth;
    QColor shapecolor;
    QPen pen;
    QJsonObject jsonObj;
    shape::code saveShape;
    int polygonSides;

};


#endif // SHAPE_H
