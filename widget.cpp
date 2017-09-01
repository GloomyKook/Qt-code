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
        if(currentShape != 0)   //�ж�ѡ�����״
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
        if(currentShape == 0&& (!list.isEmpty())) //�ж��Ƿ�ѡ��ͼ��
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

void drawWidget::removeshape() //������ǰ����ͼ��
{
        if(!list.isEmpty())
        {  relist.append(list.back());
           list.removeLast();
           update();
        }
}
void drawWidget::backshape() //���س���
{
        if(!relist.isEmpty())
        {
            list.append(relist.back());
            relist.removeLast();
            update();
        }
}
void drawWidget::saveJson(bool) //����json
{
    QFile file("test.json");
    file.open(QIODevice::WriteOnly );
    QJsonArray array;
    foreach(shape *line, list)
    {
        array.append(line->setjson());
    }
    //����json�ĵ�
    QJsonDocument documnet;
    documnet.setArray(array);
    QByteArray byte_array = documnet.toJson(QJsonDocument::Compact);
    QString json_str(byte_array);
    file.write(byte_array);
    file.close();
    qDebug()<<json_str;

}

void drawWidget::openJson(bool ) //����json
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

void drawWidget::calculateDistance(QPoint &p)  //����ѡ����ͼ�εľ���
{
    lineDistance = -1;
    rectDistance = -1;
    ellipseDistance = -1;
    polygonDistance = -1;
    for(int i=0; i< list.size();i++)
    {
        if(list.at(i)->getShape() == shape::line)  //ֱ��
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
        if(list.at(i)->getShape() == shape::reck) //����
        {
            if((p.y() <= list.at(i)->startpoint().y()) && (p.x() >= list.at(i)->startpoint().x())
                    &&(p.x() <= list.at(i)->endpoint().x()))
            {
                double a = fabs(p.y() - list.at(i)->startpoint().y()); //�ھ������Ϸ�
                if((rectDistance >= a)||(rectDistance == -1))
                {
                    rectDistance = a;
                    reckLine = list.at(i);

                }
            }
            if(p.y() >=list.at(i)->endpoint().y() && (p.x() >= list.at(i)->startpoint().x())
                    &&(p.x() <= list.at(i)->endpoint().x()))
            {
                double a = fabs(p.y() - list.at(i)->endpoint().y());  //�ھ��ε����·�
                if((rectDistance >= a)||(rectDistance == -1))
                {
                    rectDistance = a;
                    reckLine = list.at(i);
                }
            }
            if(p.x() <= list.at(i)->startpoint().x() && p.y() >= list.at(i)->startpoint().y()
                    && p.y() <= list.at(i)->endpoint().y())
            {
                double a = fabs(p.x() - list.at(i)->startpoint().x()); //�ھ��ε�����
                if((rectDistance >= a)||(rectDistance == -1))
                {
                    rectDistance = a;
                    reckLine = list.at(i);
                }
            }
            if(p.x() >= list.at(i)->endpoint().x() && p.y() >= list.at(i)->startpoint().y()
                    && p.y() <= list.at(i)->endpoint().y())
            {
                double a = fabs(p.x() - list.at(i)->endpoint().x());  //�ھ��ε����ҷ�
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
                if(a >= d)                                               //�ھ����ڲ�
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
        if(list.at(i)->getShape() == shape::ellipse ) //��Բ
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
                double k = (p.y() - list.at(i)->startpoint().y()) / (p.x() - list.at(i)->startpoint().x()); //ѡ��ĵ㵽��Բ���ĵ�ֱ�ߵ�б��
                double c = sqrt(pow((p.x() - list.at(i)->startpoint().x()),2) + pow((p.y() -list.at(i)->startpoint().y()),2));//ѡ��ĵ㵽��Բ���ĵľ���
                //ѡ��ĵ㵽��ԲԲ�ĵ������ϵ���Բ�ϵ�һ�㵽��ԲԲ�ĵľ���
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
        if(list.at(i)->getShape() == shape::polygon)   //�����
        {
            double a = sqrt(pow((list.at(i)->startpoint().x() - list.at(i)->endpoint().x()),2)
                           + pow((list.at(i)->startpoint().y()-list.at(i)->endpoint().y()),2));//����ζ��㵽���ĵľ���
            double b = sqrt(pow((list.at(i)->startpoint().x() - p.x()),2)
                            + pow((list.at(i)->startpoint().y() - p.y()),2)); //�жϵ㵽���ĵľ���
            double c = a * cos(3.1415 /list.at(i)->getsideNum()); //��������ĵ��ߵľ���
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


