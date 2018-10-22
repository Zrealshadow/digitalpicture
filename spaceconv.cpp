#include "spaceconv.h"
#include "ui_spaceconv.h"
#include "sp_func.h"
extern QImage *img,*new_img;
Spaceconv::Spaceconv(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Spaceconv)
{
    ui->setupUi(this);
}

Spaceconv::~Spaceconv()
{
    delete ui;
}

void Spaceconv::on_spaceconv_transfer_clicked()
{
    QString sx,sy,content;
    sx=ui->spaceconv_Kernal_X->text();
    sy=ui->spaceconv_Kernal_Y->text();
    content=ui->spaceconv_kernal->text();
    int xx,yy;
    bool okx,oky;
    xx=sx.toInt(&okx);
    yy=sx.toInt(&oky);
    if(!oky or !okx){
        QMessageBox::information(NULL,tr("Fail"),tr("the input type is error!"));

    }
    else{
        filter_operate filter_kernal=sp_func::struct_filter(xx,yy,content);
        int n=filter_kernal.size();
        if(n==0){
            QMessageBox::information(NULL,tr("Fail"),tr("the kernal content is error "));
        }
        else{
            new_img=sp_func::func_filter_trans(img,filter_kernal);
            this->fig_spaceconv->setPixmap(QPixmap::fromImage(*new_img));
            this->close();
        }
    }
}
