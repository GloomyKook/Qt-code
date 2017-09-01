#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include"shape.h"
#include"line.h"
#include"Rect.h"
#include"Ellipse.h"
#include "polygon.h"
#include<QPaintEvent>
#include<QPen>
#include<QLabel>
#include<QComboBox>
#include<QSpinBox>
#include<QList>
#include<QJsonDocument>
#include<cmath>
class drawWidget : public QWidget
{
    Q_OBJECT

public:
    drawWidget(QWidget *parent = 0);
    ~drawWidget();
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);

    void setcolor(QColor);
    void setcurrentstyle(int);
    void calculateDistance(QPoint &p);
    //void setSelectStyle(int);

public slots:

    void setcurrentwidth(int );
    void removeshape();
    void backshape();

    void currentshape(shape::code);
    void saveJson(bool);
    void openJson(bool);
    void polygonSides(int);
    void selectOperate();
    void reDrawShape();

    //void selectWidth(int);


private:
    QList<shape*>list;
    QList<shape*>relist;
    shape *line;
    shape::code currentShape;

    int currentwidth;
    QColor currentcolor;
    int currentstyle;
    int currentsides;

    double lineDistance ;
    double rectDistance ;
    double ellipseDistance ;
    double polygonDistance ;
    shape *lineLine;
    shape *reckLine;
    shape *ellipseLine;
    shape *polygonLine;
    shape *selectLine;

    QPoint start;
    QPoint end;
    QPoint selectPoint;
    int red;
    int green;
    int blue;
    int startX;
    int startY;
    int endX;
    int endY;
    int jsonshape;

};

#endif // WIDGET_H
