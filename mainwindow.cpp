#include "mainwindow.h"
#include"widget.h"
#include<QColorDialog>
#include<QToolBar>
#include<QFile>
#pragma execution_character_set("utf-8")
mainwindow::mainwindow(QWidget *parent) : QMainWindow(parent)
{
     draw=new drawWidget;
     setCentralWidget(draw);
     createToolBar();
     createAction();
     createMenuBar();
     setMinimumSize(600,600);

     showstyle();
     draw->setcurrentwidth(widthSpinBox->value());
     draw->setcolor(Qt::black);

     draw->currentshape(shape::None);
     draw->polygonSides(polygonSpinbox->value());

}
mainwindow::~mainwindow()
{

}

void mainwindow::createAction()
{
    openAct = new QAction(tr("��"),this);
    openAct->setShortcut(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));

    saveAct = new QAction(tr("����"),this);
    saveAct->setCheckable(true);
    saveAct->setShortcut(QKeySequence::Save);
    saveAct->setStatusTip(tr("save a file"));

    exitAct = new QAction(tr("�ر�"),this);
    exitAct->setShortcuts(QKeySequence::Close);
    exitAct->setStatusTip(tr("close a file"));

    connect(openAct,SIGNAL(triggered(bool)),draw,SLOT(openJson(bool)));
    connect(saveAct,SIGNAL(triggered(bool)),draw,SLOT(saveJson(bool)));
    connect(exitAct,SIGNAL(triggered()),this,SLOT(close()));
}

void mainwindow::createMenuBar()
{
    QMenu *filemenu = menuBar()->addMenu(tr("�˵�"));
    filemenu->addAction(openAct);
    filemenu->addAction(saveAct);
    filemenu->addAction(exitAct);
}

void mainwindow::createToolBar()
{
    QToolBar *toolbar = addToolBar(tr("tool"));


    widthLabel = new QLabel(tr("���:"));
    widthSpinBox = new QSpinBox;
    widthSpinBox->setRange(0,20);
    widthSpinBox->setValue(1);
    connect(widthSpinBox,SIGNAL(valueChanged(int)),draw,SLOT(setcurrentwidth(int)));

    styleLabel=new QLabel(tr("style:"));
    stylecombox=new QComboBox;
    stylecombox->addItem(tr("solidLine"),static_cast<int>(Qt::SolidLine));
    stylecombox->addItem(tr("DashLine"), static_cast<int>(Qt::DashLine));

    stylecombox->addItem(tr("DotLine"),
                                static_cast<int>(Qt::DotLine));
    stylecombox->addItem(tr("DashDotline"),
                                static_cast<int>(Qt::DashDotDotLine));
    stylecombox->addItem(tr("DashDotDotLine"),
                                static_cast<int>(Qt::DashDotDotLine));
    stylecombox->addItem(tr("CustomDashLine"),
                                static_cast<int>(Qt::CustomDashLine));

    connect(stylecombox,SIGNAL(activated(int)),this,SLOT(showstyle()));

    colorbtn = new QToolButton;//������ɫѡ��ؼ�
    QPixmap pixmap(20,20);
    pixmap.fill(Qt::black);
    colorbtn->setIcon(QIcon(pixmap));
    connect(colorbtn,SIGNAL(clicked()),this,SLOT(showcolor()));

    removebtn = new QToolButton;
    removebtn->setText(tr("����ͼ��"));
    connect(removebtn,SIGNAL(clicked()),draw,SLOT(removeshape()));

    backbtn = new QToolButton;
    backbtn->setText(tr("�ָ�����"));
    connect(backbtn,SIGNAL(clicked()),draw,SLOT(backshape()));

    selectBtn = new QToolButton;
    selectBtn->setText(tr("ѡ��"));
    connect(selectBtn,SIGNAL(clicked()),draw,SLOT(selectOperate()));

    toolbar->addWidget(widthLabel);
    toolbar->addWidget(widthSpinBox);
    toolbar->addWidget(colorbtn);
    toolbar->addWidget(styleLabel);
    toolbar->addWidget(stylecombox);
    toolbar->addWidget(removebtn);
    toolbar->addWidget(backbtn);
    toolbar->addWidget(selectBtn);

    QToolBar *shapeTool = addToolBar(tr("��״"));

    shapeLabel = new QLabel(tr("��״��"));
    linebtn = new QToolButton;
    linebtn->setText(tr("ֱ��"));

    connect(linebtn,SIGNAL(clicked()),this,SLOT(drawLineActionTriggered()));

    reckbtn=new QToolButton;
    reckbtn->setText(tr("����"));
    connect(reckbtn,SIGNAL(clicked()),this,SLOT(drawRectActionTriggered()));



    ellipseBtn = new QToolButton;
    ellipseBtn->setText(tr("Բ"));
    connect(ellipseBtn,SIGNAL(clicked()),this,SLOT(drawEllipseTriggered()));

    polygonBtn = new QToolButton;
    polygonBtn->setText(tr("�����"));
    connect(polygonBtn,SIGNAL(clicked()),this,SLOT(drawPolygonTriggered()));
    polygonLabel = new QLabel(tr("������:"));
    polygonSpinbox = new QSpinBox;
    polygonSpinbox->setRange(5,100);
    connect(polygonSpinbox,SIGNAL(valueChanged(int)),draw,SLOT(polygonSides(int)));

    shapeTool->addWidget(shapeLabel);
    shapeTool->addWidget(linebtn);
    shapeTool->addWidget(reckbtn);
    shapeTool->addWidget(ellipseBtn);
    shapeTool->addWidget(polygonBtn);
    shapeTool->addWidget(polygonLabel);
    shapeTool->addWidget(polygonSpinbox);

    connect(this,SIGNAL(changeCurrentsChape(shape::code)),draw,SLOT(currentshape(shape::code)));
    statusBar();
}

void mainwindow::showcolor()
{
    QColor color=QColorDialog::getColor(Qt::black,this);
    //ʹ�ñ�׼��ɫ�Ի���QColorDialog�����ɫֵ
    if(color.isValid())
    {
        draw->setcolor(color);
        QPixmap p(20,20);
        p.fill(color);
        colorbtn->setIcon(QIcon(p));
    }
}

void mainwindow::showstyle()
{
   draw->setcurrentstyle(stylecombox->itemData(stylecombox->currentIndex(),Qt::UserRole).toInt());
}

void mainwindow::drawLineActionTriggered()
{
   emit changeCurrentsChape(shape::line);
}

void mainwindow::drawRectActionTriggered()
{
    emit changeCurrentsChape(shape::reck);
}

void mainwindow::drawEllipseTriggered()
{
    emit changeCurrentsChape(shape::ellipse);
}

void mainwindow::drawPolygonTriggered()
{
    emit changeCurrentsChape(shape::polygon);
}
