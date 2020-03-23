#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QtGui>
#include "dialog.h"
#include "dialog2.h"
#include <QMap>
#include <QFileDialog>
#include <QMessageBox>
#include <QList>
#include<set>
#include<QLabel>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void Paint();
    void Paint_Line(double x1,double y1,double x2,double y2);
    void Paint_Ray(double x1,double y1,double x2,double y2);
    void Paint_Segment(double x1,double y1,double x2,double y2);
    void Paint_Cycle(double x,double y,double r);
    std::set<std::pair<double, double>> intersect_point;
private:
    Ui::MainWindow *ui;
    QImage image;
    Dialog *dialog1;
    Dialog2 *dialog2;

protected:
    void paintEvent(QPaintEvent *){
        QPainter painter(this);
        painter.drawImage(0,0,image);
    }

private slots:
    void on_pushButton_clicked();
    void receiveData(int type,QString name,QString x1,QString y1,QString x2,QString y2);
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

signals:
    void sendGraph(QMap<QString,int>,QMap<QString,QPair<QPointF,QPointF>>);
};

#endif // MAINWINDOW_H
