#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QLabel>
#include<QComboBox>
#include<QSpinBox>
#include<QColor>
#include"widget.h"
#include<QToolButton>
#include"shape.h"
#include<QAction>
#include<QMenuBar>
class mainwindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit mainwindow(QWidget *parent = 0);
    ~mainwindow();
    void createToolBar();
    void createAction();
    void createMenuBar();

    drawWidget *draw;

signals:
    void changeCurrentsChape(shape::code newShape);

public slots:
    void showcolor();
    void showstyle();

    void drawLineActionTriggered();
    void drawRectActionTriggered();
    void drawEllipseTriggered();
    void drawPolygonTriggered();


private:

    //shape *newshape;
    QLabel *styleLabel;
    QLabel *widthLabel;
    QLabel *shapeLabel;
    QSpinBox *widthSpinBox;
    QColor *color;
    QToolButton *colorbtn;
    QComboBox *stylecombox;
    QToolButton *removebtn;
    QToolButton *backbtn;
    QToolButton *linebtn;
    QToolButton *reckbtn;
    QToolButton *ellipseBtn;
    QToolButton *polygonBtn;
    QLabel *polygonLabel;
    QSpinBox *polygonSpinbox;
    QToolButton *selectBtn;

    QAction *openAct;
    QAction *saveAct;
    QAction *exitAct;



};

#endif // MAINWINDOW_H
