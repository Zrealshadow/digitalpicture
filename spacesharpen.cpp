#include "spacesharpen.h"
#include "ui_spacesharpen.h"
#include "sp_func.h"
typedef std::vector<std::vector<int>>  filter_operate;
extern QImage *img,*new_img;
Spacesharpen::Spacesharpen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Spacesharpen)
{
    ui->setupUi(this);
}

Spacesharpen::~Spacesharpen()
{
    delete ui;
}

void Spacesharpen::on_sharpen_roberts_clicked()
{
    filter_operate filter_x,filter_y;
    filter_x=sp_func::struct_filter(2,2,"1,0,0,-1");
    filter_y=sp_func::struct_filter(2,2,"0,1,-1,0");
    QImage *imgx,*imgy;
    imgx=sp_func::func_filter_trans(img,filter_x);
    imgy=sp_func::func_filter_trans(img,filter_y);
    for(int y=0;y<img->height();y++){
        for(int x=0;x<img->width();x++){
            int v_x=qRed(imgx->pixel(x,y));
            int v_y=qRed(imgy->pixel(x,y));
            int v=v_x+v_y;
            new_img->setPixel(x,y,qRgb(v,v,v));
        }
    }
    this->fig_spacesharpen->setPixmap(QPixmap::fromImage(*new_img));
    this->close();
}

void Spacesharpen::on_sharpen_laplace_clicked()
{

}

void Spacesharpen::on_sharpen_sobel_clicked()
{

}

void Spacesharpen::on_sharpen_prewitt_clicked()
{

}
