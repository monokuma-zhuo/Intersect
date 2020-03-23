#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    image = QImage(600,600,QImage::Format_RGB32);
    QColor backColor = qRgb(255,255,255);
    image.fill(backColor);
    Paint();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    dialog1=new Dialog;
    connect(dialog1,SIGNAL(sendData(int,QString,QString,QString,QString,QString)),this,SLOT(receiveData(int,QString,QString,QString,QString,QString)));
    dialog1->show();
}

void MainWindow::receiveData(int type,QString name,QString x1,QString y1,QString x2,QString y2)
{
    if(type==0){
        Paint_Line(x1.toDouble(),y1.toDouble(),x2.toDouble(),y2.toDouble());
    }
    else if(type==1){
        Paint_Ray(x1.toDouble(),y1.toDouble(),x2.toDouble(),y2.toDouble());
    }
    else if(type==2){
        Paint_Segment(x1.toDouble(),y1.toDouble(),x2.toDouble(),y2.toDouble());
    }
    else if(type==3){
        Paint_Cycle(x1.toDouble(),y1.toDouble(),x2.toDouble());
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    image.fill(Qt::white);
    Paint();
    update();
}

void MainWindow::on_pushButton_3_clicked()
{
    QString filename;
    filename=QFileDialog::getOpenFileName(this,tr("文件"),"",tr("text(*.txt)"));
    if(!filename.isNull())
    {
        QFile file(filename);
        if(!file.open(QFile::ReadOnly|QFile::Text))
        {
            QMessageBox::warning(this,tr("error"),tr("read file error:&1").arg(file.errorString()));
            return;
        }
        QTextStream in(&file);
        while(!in.atEnd())
        {
            QString line=in.readLine();
            QList<QString> list;
            list=line.split(' ');
            if(list[0]=="L")
            {
                Paint_Line(list[1].toDouble(),list[2].toDouble(),list[3].toDouble(),list[4].toDouble());
            }
            else if(list[0]=="R")
            {
                Paint_Ray(list[1].toDouble(),list[2].toDouble(),list[3].toDouble(),list[4].toDouble());
            }
            else if(list[0]=="S")
            {
                Paint_Segment(list[1].toDouble(),list[2].toDouble(),list[3].toDouble(),list[4].toDouble());
            }
            else if(list[0]=="C")
            {
                Paint_Cycle(list[1].toDouble(),list[2].toDouble(),list[3].toDouble());
            }
        }
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    std::set<std::pair<double, double>>::iterator it;
    for(it=intersect_point.begin();it!=intersect_point.end();it++)
    {
        QString x=QString::number((*it).first,'f',1);
        QString y=QString::number((*it).second,'f',1);
        QLabel *text=new QLabel(this);
        text->setText("("+x+","+y+")");
        text->setGeometry(300+(*it).first,300-(*it).second,100,25);
        text->show();
    }
}
