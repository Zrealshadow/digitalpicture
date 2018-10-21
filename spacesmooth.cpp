#include "spacesmooth.h"
#include "ui_spacesmooth.h"
#include "sp_func.h"
Spacesmooth::Spacesmooth(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Spacesmooth)
{
    ui->setupUi(this);
    ui->smooth_k->insert("5");
}

Spacesmooth::~Spacesmooth()
{
    delete ui;
}

extern QImage *img,*new_img;
void Spacesmooth::on_smooth_average_clicked()
{
    new_img=sp_func::func_smooth_average(img);
    this->fig_spacesmooth->setPixmap(QPixmap::fromImage(*new_img));
    this->close();
}

void Spacesmooth::on_smooth_middle_clicked()
{
    new_img=sp_func::func_smooth_middle(img);
    this->fig_spacesmooth->setPixmap(QPixmap::fromImage(*new_img));
    this->close();
}

void Spacesmooth::on_smooth_kllinear_clicked()
{
    QString sk=ui->smooth_k->text();
    int k;
    bool ok;
    k=sk.toInt(&ok);
    if(!ok){
        QMessageBox::information(NULL,Spacesmooth::tr("Fail"),Spacesmooth::tr("the input is error!"));
    }
    else{
        new_img=sp_func::func_smooth_klinear(img,k);
        this->fig_spacesmooth->setPixmap(QPixmap::fromImage(*new_img));
        this->close();
    }
}
