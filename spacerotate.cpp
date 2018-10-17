#include "spacerotate.h"
#include "ui_spacerotate.h"
#include "sp_func.h"
extern QImage *img;
extern QImage * new_img;

Spacerotate::Spacerotate(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Spacerotate)
{

    ui->setupUi(this);
    ui->rotate_center_X->insert(QString::number((int)img->width(),10));
    ui->rotate_center_Y->insert(QString::number((int)img->height(),10));
}

Spacerotate::~Spacerotate()
{

    delete ui;
}

void Spacerotate::on_rotate_doublelinear_clicked()
{
    QString tcx,tcy,ta;
    tcx=ui->rotate_center_X->text();
    tcy=ui->rotate_center_Y->text();
    ta=ui->rotate_angle->text();
    bool xok,yok,aok;
    int cx,cy;
    double a;
    cx=tcx.toInt(&xok);
    cy=tcy.toInt(&yok);
    a=ta.toDouble(&aok);
    if(!xok or !yok or !aok){
        QMessageBox::information(NULL,Spacerotate::tr("Fail"),Spacerotate::tr("the input is error"));
    }
    else{
        new_img=sp_func::func_rotate_DoubleLinear(new_img,cx,cy,a);
        this->fig_spacerotate->setPixmap(QPixmap::fromImage(*new_img));
        this->close();
    }
}

void Spacerotate::on_rotate_nearby_clicked()
{
    QString tcx,tcy,ta;
    tcx=ui->rotate_center_X->text();
    tcy=ui->rotate_center_Y->text();
    ta=ui->rotate_angle->text();
    bool xok,yok,aok;
    int cx,cy;
    double a;
    cx=tcx.toInt(&xok);
    cy=tcy.toInt(&yok);
    a=ta.toDouble(&aok);
    if(!xok or !yok or !aok){
        QMessageBox::information(NULL,Spacerotate::tr("Fail"),Spacerotate::tr("the input is error"));
    }
    else{
        new_img=sp_func::func_rotate_Nearby(new_img,cx,cy,a);
        this->fig_spacerotate->setPixmap(QPixmap::fromImage(*new_img));
        this->close();
    }
}

