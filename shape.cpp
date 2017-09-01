#include "shape.h"
#include<QWidget>
shape::shape()
{    
}

void shape::setstrat(QPoint s)
{
    start = s;


}
QPoint shape::startpoint()
{
    return start;
}
void shape::setend(QPoint e)
{
    end = e;

}
 QPoint shape::endpoint()
 {
     return end;
 }

void shape::setshapewidth(int w)
{
    shapewidth = w;

}
int shape ::getwidth()
{
    return shapewidth;
}
void shape::setshapecolor(QColor c)
{
    shapecolor = c;

}
QColor shape::getColor()
{
    return shapecolor;
}
void shape::setshapestyle(int s)
{
    shapestyle = s;

}

int shape::getStyle()
{
    return shapestyle;
}

void shape::setshape(shape::code c)
{
    saveShape = c;
}

shape::code shape::getShape()
{
    return saveShape;
}

void shape::sideNum(int s)
{
    polygonSides = s;
}

int shape::getsideNum()
{
    return polygonSides;
}
QJsonObject shape::setjson() //把形状的数据保存以json的格式保存起来
{
    jsonObj.insert("shape",saveShape);
    jsonObj.insert("startX",start.x());
    jsonObj.insert("startY",start.y());

    jsonObj.insert("endX",end.x());
    jsonObj.insert("endY",end.y());

    jsonObj.insert("shapewidth",shapewidth);

    jsonObj.insert("colorRed",shapecolor.red());
    jsonObj.insert("colorGreen",shapecolor.green());
    jsonObj.insert("colorBlue",shapecolor.blue());

    jsonObj.insert("shapestyle",shapestyle);
    jsonObj.insert("polygonSides",polygonSides);

    return jsonObj;

}

