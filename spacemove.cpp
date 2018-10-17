#include "spacemove.h"
#include "ui_spacemove.h"
#include "sp_func.h"
extern QImage *new_img;
extern QImage *img;
Spacemove::Spacemove(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Spacemove)
{
    ui->setupUi(this);
}

Spacemove::~Spacemove()
{
    delete ui;
}

void Spacemove::on_spacemove_move_clicked()
{
    QString sx=ui->space_moveX->text();
    QString sy=ui->space_moveY->text();
    bool x_ok,y_ok;
    int dx,dy;
    dx=sx.toInt(&x_ok);
    dy=sy.toInt(&y_ok);
    if(x_ok and y_ok){
        new_img=sp_func::func_move(img,dx,dy);
        this->fig_spacemove->setPixmap(QPixmap::fromImage(*new_img));
        this->close();
    }
    else{
        QMessageBox::information(NULL,Spacemove::tr("Fail"),Spacemove::tr("the input is error!"));
    }
}

void Spacemove::on_spacemove_quit_clicked()
{
    this->close();
}
