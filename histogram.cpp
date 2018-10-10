#include "histogram.h"
#include "ui_histogram.h"
extern QImage *img;
extern QImage *new_img;
Histogram::Histogram(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Histogram)
{
    ui->setupUi(this);
    ui->hist_1=hist_func::plot_histogram(ui->hist_1,img);
    ui->hist_2=hist_func::plot_histogram(ui->hist_2,new_img);

}

Histogram::~Histogram()
{
    delete ui;
}

extern QImage *img;

void Histogram::on_quit_clicked()
{
    this->close();
}
