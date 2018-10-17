#include "spacezoom.h"
#include "ui_spacezoom.h"
#include "sp_func.h"
extern QImage *img;
extern QImage *new_img;
Spacezoom::Spacezoom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Spacezoom)
{
    ui->setupUi(this);
}

Spacezoom::~Spacezoom()
{
    delete ui;
}


void Spacezoom::on_pushButton_clicked()
{
    QString t=ui->space_multi->text();
    double coef;
    bool ok=false;
    coef=t.toDouble(&ok);
    if(!ok){
        QMessageBox::information(NULL,Spacezoom::tr("Fail"),Spacezoom::tr("the input is error"));
    }
    else{
        new_img=sp_func::func_zoom_in_out(new_img,coef);
        this->fig_spacezoom->setPixmap(QPixmap::fromImage(*new_img));
        this->close();
    }

}

void Spacezoom::on_zoom_nearby_clicked()
{
    QString t=ui->space_multi->text();
    double coef;
    bool ok=false;
    coef=t.toDouble(&ok);
    if(!ok){
        QMessageBox::information(NULL,Spacezoom::tr("Fail"),Spacezoom::tr("the input is error"));
    }
    else{
        new_img=sp_func::func_zoom_nearby(new_img,coef);
        this->fig_spacezoom->setPixmap(QPixmap::fromImage(*new_img));
        this->close();

    }
}
