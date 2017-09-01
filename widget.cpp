#include "widget.h"

drawWidget::drawWidget(QWidget *parent)
    : QWidget(parent)
{

}

drawWidget::~drawWidget()
{

}

void drawWidget::currentshape(shape::code c)
{
    if(c!=currentShape)
    {
        currentShape=c;
    }

}

void drawWidget::setcolor(QColor p)
{

    currentcolor=p;

}
void drawWidget::setcurrentwidth(int w)
{
    currentwidth=w;

}
void drawWidget::setcurrentstyle(int s)
{
    currentstyle=s;

}

void drawWidget::polygonSides(int s)
{
    currentsides = s;

}

void drawWidget::selectOperate()
{
    currentShape = shape::None;


}
void drawWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    foreach (shape*line, list)
    {

        line->paint(painter);

    }
}

void drawWidget::mousePressEvent(QMouseEvent *event)
{
        if(currentShape != 0)   //判断选择的形状
        {
            switch (currentShape)
            {
            case shape::line:
                line = new Line;
                break;
            case shape::reck:
                line = new Rect;
                break;
            case shape::ellipse:
                line = new ellipse;
                break;
            case shape::polygon:
                line = new polygon;
                break;
            }
            if(currentShape ==shape::polygon)
                line->sideNum(currentsides);
            if(event->button() == Qt::LeftButton)
           {
                list << line;
                line->setshape(currentShape);
                line->setstrat(event->pos());
                line->setend(event->pos());
                line->setshapewidth(currentwidth);
                line->setshapecolor(currentcolor);
                line->setshapestyle(currentstyle);
            }
            update();
        }
        if(currentShape == 0&& (!list.isEmpty())) //判断是否选择图形
        {
            selectPoint = event->pos();
            qDebug()<<selectPoint;
            calculateDistance(selectPoint);
            reDrawShape();
            update();
        }
}
void drawWidget::mouseMoveEvent(QMouseEvent *e)
{    
    if(currentShape != 0)
        {

            line->setend(e->pos());
            update();
        }
}

void drawWidget::removeshape() //撤销当前画的图形
{
        if(!list.isEmpty())
        {  relist.append(list.back());
           list.removeLast();
           update();
        }
}
void drawWidget::backshape() //返回撤销
{
        if(!relist.isEmpty())
        {
            list.append(relist.back());
            relist.removeLast();
            update();
        }
}
void drawWidget::saveJson(bool) //设置json
{
    QFile file("test.json");
    file.open(QIODevice::WriteOnly );
    QJsonArray array;
    foreach(shape *line, list)
    {
        array.append(line->setjson());
    }
    //构建json文档
    QJsonDocument documnet;
    documnet.setArray(array);
    QByteArray byte_array = documnet.toJson(QJsonDocument::Compact);
    QString json_str(byte_array);
    file.write(byte_array);
    file.close();
    qDebug()<<json_str;

}

void drawWidget::openJson(bool ) //解析json
{
    QFile file("test.json");
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QByteArray json = file.readAll();
    file.close();
    QString json_str(json);
    //qDebug()<<json_str;
    QJsonParseError jsonError;
    QJsonDocument doucment = QJsonDocument::fromJson(json,&jsonError);
    //qDebug()<<jsonError.error;
    if(!doucment.isNull() &&jsonError.error == QJsonParseError::NoError)
    {
        if(doucment.isArray())
        {
            QJsonArray array = doucment.array();
            int size = array.size();
            for(int i=0; i<size; ++i)
            {
               QJsonObject object = array[i].toObject();
               if(object.contains("shape"))
               {
                   QJsonValue value = object["shape"];
                   jsonshape = value.toInt();
               }

               if(object.contains("startX"))
               {
                    QJsonValue value = object["startX"];
                    startX = value.toInt();
               }

               if(object.contains("startY"))
               {
                   QJsonValue value = object["startY"];
                   startY = value.toInt();
               }

               if(object.contains("endX"))
               {
                   QJsonValue value = object["endX"];
                   endX = value.toInt();
               }
               if(object.contains("endY"))
               {
                   QJsonValue value = object["endY"];
                   endY = value.toInt();
               }
               if(object.contains("shapewidth"))
               {
                   QJsonValue value = object["shapewidth"];
                   currentwidth = value.toInt();
                   //qDebug()<<currentShape;
               }

               if(object.contains("shapestyle"))
               {
                   QJsonValue value = object["shapestyle"];
                   currentstyle = value.toInt();
                   //qDebug()<<currentstyle;
               }

               if(object.contains("colorRed"))
               {
                   QJsonValue value = object["colorRed"];
                   red = value.toInt();
               }

               if(object.contains("colorGreen"))
               {
                   QJsonValue value = object["colorGreen"];
                   green = value.toInt();
               }

               if(object.contains("colorBlue"))
               {
                   QJsonValue value = object["colorBlue"];
                   blue = value.toInt();
               }
               if(object.contains("polygonSides"))
               {
                   QJsonValue value = object["polygonSides"];
                   currentsides = value.toInt();

               }
               currentShape = shape::code(jsonshape);
               start.setX(startX);
               start.setY(startY);
               //qDebug()<<start;
               end.setX(endX);
               end.setY(endY);
               //qDebug()<<end;
               currentcolor.setRgb(red,green,blue);


               switch (currentShape)
               {
               case shape::line:
                   line = new Line;
                   break;
               case shape::reck:
                   line = new Rect;
                   break;
               case shape::ellipse:
                   line = new ellipse;
                   break;
               case shape::polygon:
                   line = new polygon;

               }
               if(currentShape ==shape::polygon)
                   line->sideNum(currentsides);
               list<<line;
               line->setshape(currentShape);
               line->setshapewidth(currentwidth);
               line->setshapecolor(currentcolor);
               line->setshapestyle(currentstyle);
               line->setstrat(start);
               line->setend(end);
            }
            update();
        }
    }
    else {
        qDebug()<<"this is error!";

    }
}

void drawWidget::calculateDistance(QPoint &p)  //计算选择点和图形的距离
{
    lineDistance = -1;
    rectDistance = -1;
    ellipseDistance = -1;
    polygonDistance = -1;
    for(int i=0; i< list.size();i++)
    {
        if(list.at(i)->getShape() == shape::line)  //直线
        {

            double a = list.at(i)->endpoint().y() - list.at(i)->startpoint().y();
            double b = list.at(i)->startpoint().x() - list.at(i)->endpoint().x();
            double c = list.at(i)->startpoint().y() * list.at(i)->endpoint().x() - list.at(i)->startpoint().x() * list.at(i)->endpoint().y();
            double d = fabs(a*p.x()+b*p.y()+c) / sqrt(a*a+b*b);
            if((lineDistance >= d) ||(lineDistance  ==-1))
            {
                lineDistance = d;
                lineLine = list.at(i);

                qDebug()<<"line:"<<lineLine;                
            }
        }
        if(list.at(i)->getShape() == shape::reck) //矩形
        {
            if((p.y() <= list.at(i)->startpoint().y()) && (p.x() >= list.at(i)->startpoint().x())
                    &&(p.x() <= list.at(i)->endpoint().x()))
            {
                double a = fabs(p.y() - list.at(i)->startpoint().y()); //在矩形正上方
                if((rectDistance >= a)||(rectDistance == -1))
                {
                    rectDistance = a;
                    reckLine = list.at(i);

                }
            }
            if(p.y() >=list.at(i)->endpoint().y() && (p.x() >= list.at(i)->startpoint().x())
                    &&(p.x() <= list.at(i)->endpoint().x()))
            {
                double a = fabs(p.y() - list.at(i)->endpoint().y());  //在矩形的正下方
                if((rectDistance >= a)||(rectDistance == -1))
                {
                    rectDistance = a;
                    reckLine = list.at(i);
                }
            }
            if(p.x() <= list.at(i)->startpoint().x() && p.y() >= list.at(i)->startpoint().y()
                    && p.y() <= list.at(i)->endpoint().y())
            {
                double a = fabs(p.x() - list.at(i)->startpoint().x()); //在矩形的正左方
                if((rectDistance >= a)||(rectDistance == -1))
                {
                    rectDistance = a;
                    reckLine = list.at(i);
                }
            }
            if(p.x() >= list.at(i)->endpoint().x() && p.y() >= list.at(i)->startpoint().y()
                    && p.y() <= list.at(i)->endpoint().y())
            {
                double a = fabs(p.x() - list.at(i)->endpoint().x());  //在矩形的正右方
                if((rectDistance >= a)||(rectDistance == -1))
                {
                    rectDistance = a;
                    reckLine = list.at(i);
                }

            }
            if(p.x() >= list.at(i)->startpoint().x() && p.x() <= list.at(i)->endpoint().x()
                    && p.y() >= list.at(i)->startpoint().y() && p.y() <= list.at(i)->endpoint().y())
            {
                double b = fabs(list.at(i)->startpoint().x() - p.x());
                double c = fabs(list.at(i)->startpoint().y() - p.y());
                double d = fabs(list.at(i)->endpoint().x() - p.x());
                double f = fabs(list.at(i)->endpoint().y() - p.y());
                double a = b;
                if(a >= c)
                    a = c;
                if(a >= d)                                               //在矩形内部
                    a = d;
                if(a >= f)
                    a=f;

                if((rectDistance >= a)||(rectDistance == -1))
                    {
                        rectDistance = a;
                        reckLine = list.at(i);
                    }
            }
            qDebug()<<"rect:"<<reckLine;
        }
        if(list.at(i)->getShape() == shape::ellipse ) //椭圆
        {
            if(p.y() ==  list.at(i)->startpoint().y())
            {
                double a = fabs(p.x() - (list.at(i)->endpoint().x() - list.at(i)->startpoint().x()));
                if((ellipseDistance >= a)||(ellipseDistance == -1))
                {
                    ellipseDistance = a;
                    ellipseLine = list.at(i);
                }
            }
            if(p.x() == list.at(i)->startpoint().x())
            {
                double a = fabs(p.y() - list.at(i)->startpoint().y());
                if((ellipseDistance >= a)||(ellipseDistance == -1))
                {
                    ellipseDistance = a;
                    ellipseLine = list.at(i);
                }
            }
            if(p.x() !=  list.at(i)->startpoint().x() && p.y() != list.at(i)->startpoint().y())
            {
                double k = (p.y() - list.at(i)->startpoint().y()) / (p.x() - list.at(i)->startpoint().x()); //选择的点到椭圆中心的直线的斜率
                double c = sqrt(pow((p.x() - list.at(i)->startpoint().x()),2) + pow((p.y() -list.at(i)->startpoint().y()),2));//选择的点到椭圆中心的距离
                //选择的点到椭圆圆心的连线上的椭圆上的一点到椭圆圆心的距离
                double e = sqrt(pow((cos(atan(k)) * (list.at(i)->endpoint().x() - list.at(i)->startpoint().x())),2)
                                + pow((sin(atan(k)) * (list.at(i)->endpoint().y() - list.at(i)->startpoint().y())),2));
                double a = fabs(c - e);
               if((ellipseDistance >= a)||(ellipseDistance == -1))
                {
                    ellipseDistance = a;
                    ellipseLine = list.at(i);
                }
            }
            qDebug()<<"ellipse:"<<ellipseLine;
        }
        if(list.at(i)->getShape() == shape::polygon)   //多边形
        {
            double a = sqrt(pow((list.at(i)->startpoint().x() - list.at(i)->endpoint().x()),2)
                           + pow((list.at(i)->startpoint().y()-list.at(i)->endpoint().y()),2));//多边形顶点到中心的距离
            double b = sqrt(pow((list.at(i)->startpoint().x() - p.x()),2)
                            + pow((list.at(i)->startpoint().y() - p.y()),2)); //判断点到中心的距离
            double c = a * cos(3.1415 /list.at(i)->getsideNum()); //多边形中心到边的距离
            double d = fabs(a - b);
            double e = fabs(c- b);
//            qDebug()<<d;
//            qDebug()<<e;
            if(d > e )
            {
                d =e;
            }
            if((polygonDistance >=d) ||(polygonDistance == -1))
            {
                polygonDistance = d;
                polygonLine = list.at(i);
            }
            qDebug()<<"polygon:"<<polygonLine;
        }
    }

}
void drawWidget::reDrawShape()
{
    qDebug()<<"lineDistance:"<<lineDistance;
    qDebug()<<"rectDistance:"<<rectDistance;
    qDebug()<<"ellipseDistance:"<<ellipseDistance;
    qDebug()<<"polygonDistance:"<<polygonDistance<<endl;

    if((lineDistance >= 0 )&& (lineDistance <= 3))
    {
        selectLine = lineLine;
    }
    if((rectDistance >= 0) && (rectDistance <= 3))
    {
        selectLine = reckLine;
    }
    if(ellipseDistance >= 0 && ellipseDistance <= 10)
    {
        selectLine = ellipseLine;
    }
    if(polygonDistance >= 0 && polygonDistance <= 10)
    {
        selectLine = polygonLine;
    }
    qDebug()<<selectLine;

//    int width = selectLine->getwidth();
//    QColor color = selectLine->getColor();
//    int style = selectLine->getStyle();
    selectLine->setshapewidth(currentwidth);
    selectLine->setshapestyle(currentstyle);
    selectLine->setshapecolor(currentcolor);
//    if(width !=currentwidth)
//    {
//        selectLine->setshapewidth(currentwidth);
//    }
//    if(color != currentcolor)
//    {
//        selectLine->setshapecolor(currentcolor);
//    }

//    if(style != currentstyle)
//    {
//        selectLine->setshapestyle(currentstyle);
//    }

}


