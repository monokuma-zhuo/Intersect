#include "mainwindow.h"
#include <QtGui>
#include <QPaintEvent>
#include <QApplication>
#include <QDialog>
#include <QLibrary>
#include <pch.h>
static int pointx0=300,pointy0=300;//原点坐标
LONG ApplicationCrashHandler(EXCEPTION_POINTERS *pException){//程式异常捕获
    QMessageBox::critical(NULL,"Error","intersectException");
    return EXCEPTION_EXECUTE_HANDLER;
}
void MainWindow::Paint()
{
    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing, true);//设置反锯齿模式，好看一点
    int width=600-pointx0,height=300;//确定坐标轴宽度跟高度
    painter.drawLine(pointx0,pointy0,width+pointx0,pointy0);//坐标轴x宽度为width
    painter.drawLine(pointx0,pointy0-height,pointx0,pointy0);//坐标轴y高度为height
    painter.drawLine(pointx0,pointy0,pointx0-width,pointy0);
    painter.drawLine(pointx0,pointy0,pointx0,pointy0+height);
}
void MainWindow::Paint_Line(double x1,double y1,double x2,double y2)
{
    intersect_point=input_line(std::make_pair(std::make_pair(x1,y1),std::make_pair(x2,y2)));
    QPainter painter(&image);
    QPen pen;
    pen.setColor(Qt::blue);
    painter.setPen(pen);
    painter.setRenderHint(QPainter::Antialiasing, true);
    if(x1==x2)
    {
        painter.drawLine(QPointF(pointx0+x1,0),QPointF(pointx0+x2,600));
    }
    else if(y1==y2)
    {
        painter.drawLine(QPointF(0,pointy0-y1),QPointF(600,pointy0-y2));
    }
    else{
        double k=(y2-y1)/(x2-x1);
        double b=y1-k*x1;
        painter.drawLine(QPointF(0,-1*(-300*k+b)+pointy0),QPointF(600,-1*(300*k+b)+pointy0));
    }
}
void MainWindow::Paint_Ray(double x1, double y1, double x2, double y2)
{
    intersect_point=input_ray(std::make_pair(std::make_pair(x1,y1),std::make_pair(x2,y2)));
    QPainter painter(&image);
    QPen pen;
    pen.setColor(Qt::blue);
    painter.setPen(pen);
    painter.setRenderHint(QPainter::Antialiasing, true);
    if(x1==x2)
    {
        if(y1<y2)
        {
            painter.drawLine(QPointF(pointx0+x1,pointy0-y1),QPointF(pointx0+x2,600));
        }
        else
        {
            painter.drawLine(QPointF(pointx0+x1,pointy0-y1),QPointF(pointx0+x2,0));
        }
    }
    else if(y1==y2)
    {
        if(x1<x2)
        {
            painter.drawLine(QPointF(pointx0+x1,pointy0-y1),QPointF(600,pointy0-y2));
        }
        else
        {
            painter.drawLine(QPointF(pointx0+x1,pointy0-y1),QPointF(0,pointy0-y2));
        }
    }
    else{
        double k=(y2-y1)/(x2-x1);
        double b=y1-k*x1;
        if(x1<x2){
            painter.drawLine(QPointF(pointx0+x1,pointy0-y1),QPointF(600,-1*(300*k+b)+pointy0));
        }
        else
        {
            painter.drawLine(QPointF(pointx0+x1,pointy0-y1),QPointF(0,-1*(300*k+b)+pointy0));
        }
    }
}
void MainWindow::Paint_Segment(double x1, double y1, double x2, double y2)
{
    intersect_point=input_segment(std::make_pair(std::make_pair(x1,y1),std::make_pair(x2,y2)));
    QPainter painter(&image);
    QPen pen;
    pen.setColor(Qt::blue);
    painter.setPen(pen);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.drawLine(QPointF(pointx0+x1,pointy0-y1),QPointF(pointx0+x2,pointy0-y2));
}
void MainWindow::Paint_Cycle(double x, double y, double r)
{
    intersect_point=input_circle(std::make_pair(std::make_pair(x,y),r));
    QMessageBox::information(NULL,"ErrorMessage","intersectException");
    QPainter painter(&image);
    QPen pen;
    pen.setColor(Qt::blue);
    painter.setPen(pen);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.drawEllipse(QPointF(pointx0+x,pointy0-y),r,r);
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)ApplicationCrashHandler);
    main1(argc,argv);
    return a.exec();
}
