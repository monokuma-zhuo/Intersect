#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->label->setVisible(false);
    ui->label_2->setVisible(false);
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);
    ui->label_5->setVisible(false);
    ui->lineEdit->setVisible(false);
    ui->lineEdit_2->setVisible(false);
    ui->lineEdit_3->setVisible(false);
    ui->lineEdit_4->setVisible(false);
    ui->lineEdit_5->setVisible(false);
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_radioButton_5_clicked(bool checked)
{
    if(checked==true)
    {
        ui->label->setVisible(true);
        ui->label_2->setVisible(true);
        ui->label_3->setVisible(false);
        ui->label_4->setVisible(false);
        ui->label_5->setVisible(false);
        ui->lineEdit->setVisible(true);
        ui->lineEdit_2->setVisible(true);
        ui->lineEdit_3->setVisible(true);
        ui->lineEdit_4->setVisible(true);
        ui->lineEdit_5->setVisible(false);
    }
}


void Dialog::on_radioButton_2_clicked(bool checked)
{
    if(checked==true)
    {
        ui->label->setVisible(true);
        ui->label_2->setVisible(true);
        ui->label_3->setVisible(false);
        ui->label_4->setVisible(false);
        ui->label_5->setVisible(false);
        ui->lineEdit->setVisible(true);
        ui->lineEdit_2->setVisible(true);
        ui->lineEdit_3->setVisible(true);
        ui->lineEdit_4->setVisible(true);
        ui->lineEdit_5->setVisible(false);
    }
}

void Dialog::on_radioButton_3_clicked(bool checked)
{
    if(checked==true)
    {
        ui->label->setVisible(true);
        ui->label_2->setVisible(true);
        ui->label_3->setVisible(false);
        ui->label_4->setVisible(false);
        ui->label_5->setVisible(false);
        ui->lineEdit->setVisible(true);
        ui->lineEdit_2->setVisible(true);
        ui->lineEdit_3->setVisible(true);
        ui->lineEdit_4->setVisible(true);
        ui->lineEdit_5->setVisible(false);
    }
}

void Dialog::on_radioButton_4_clicked(bool checked)
{
    if(checked==true)
    {
        ui->label->setVisible(false);
        ui->label_2->setVisible(false);
        ui->label_3->setVisible(true);
        ui->label_4->setVisible(true);
        ui->label_5->setVisible(false);
        ui->lineEdit->setVisible(true);
        ui->lineEdit_2->setVisible(true);
        ui->lineEdit_3->setVisible(true);
        ui->lineEdit_4->setVisible(false);
        ui->lineEdit_5->setVisible(false);
    }
}

void Dialog::on_buttonBox_accepted()
{
    if(ui->radioButton_5->isChecked()){
        emit sendData(0,ui->lineEdit_5->text(),ui->lineEdit->text(),ui->lineEdit_2->text(),ui->lineEdit_3->text(),ui->lineEdit_4->text());
    }
    else if(ui->radioButton_2->isChecked()){
        emit sendData(1,ui->lineEdit_5->text(),ui->lineEdit->text(),ui->lineEdit_2->text(),ui->lineEdit_3->text(),ui->lineEdit_4->text());
    }
    else if(ui->radioButton_3->isChecked()){
        emit sendData(2,ui->lineEdit_5->text(),ui->lineEdit->text(),ui->lineEdit_2->text(),ui->lineEdit_3->text(),ui->lineEdit_4->text());
    }
    else if(ui->radioButton_4->isChecked()){
        emit sendData(3,ui->lineEdit_5->text(),ui->lineEdit->text(),ui->lineEdit_2->text(),ui->lineEdit_3->text(),ui->lineEdit_4->text());
    }
}
