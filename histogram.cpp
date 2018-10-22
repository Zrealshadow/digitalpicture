#include "histogram.h"
#include "ui_histogram.h"
extern QImage *img;
extern QImage *new_img;
Histogram::Histogram(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Histogram)
{
    ui->setupUi(this);

    __init__();

}

Histogram::~Histogram()
{
    delete ui;
}


void Histogram::on_quit_clicked()
{
    this->close();
}

void Histogram::__init__(){
    ui->mean_Hist_img->clear();
    ui->mid_Hist_img->clear();
    ui->stdev_Hist_img->clear();
    ui->mean_Hist_new_img->clear();
    ui->mid_Hist_new_img->clear();
    ui->stdev_Hist_new_img->clear();
    // clear all text and graphs
    ui->cmp_img->setScaledContents(true);
    ui->cmp_new_img->setScaledContents(true);
    ui->cmp_img->setPixmap(QPixmap::fromImage(*img));
    ui->cmp_new_img->setPixmap(QPixmap::fromImage(*new_img));

    ui->hist_1=hist_func::plot_histogram(ui->hist_1,img);
    ui->hist_2=hist_func::plot_histogram(ui->hist_2,new_img);
    //plot

    QHash<QString,double>map=hist_func::hist_func_cal(img);
    ui->mean_Hist_img->insert(QString::number((int)map["Mean"],10));
    ui->mid_Hist_img->insert(QString::number((int)map["Mid"],10));
    ui->stdev_Hist_img->insert(QString::number(map["Stdev"],10,2));
    map=hist_func::hist_func_cal(new_img);
    ui->mean_Hist_new_img->insert(QString::number((int)map["Mean"],10));
    ui->mid_Hist_new_img->insert(QString::number((int)map["Mid"],10));
    ui->stdev_Hist_new_img->insert(QString::number(map["Stdev"],10,2));
    //insert text
}

void Histogram::on_pushButton_clicked()
{
    QFileDialog * fileDialog=new QFileDialog();
    fileDialog->setWindowTitle(Histogram::tr("save As"));
    fileDialog->setAcceptMode(QFileDialog::AcceptSave);
    fileDialog->setFileMode(QFileDialog::AnyFile);
    fileDialog->setViewMode(QFileDialog::Detail);
    fileDialog->setGeometry(500,300,1000,600);
    fileDialog->setDirectory("..");
    fileDialog->selectNameFilter(Histogram::tr("Image Files(*.png *.bmp *.jpg *.tif *.GIF)"));
    QString filename=fileDialog->getSaveFileName();
    if(filename.isEmpty())
    {

    }
    else
    {
        if(! ui->hist_1->savePng(filename) ) //保存图像
        {
            QMessageBox::information(NULL,
                Histogram::tr("Failed to save the image"),
                Histogram::tr("Failed to save the image!"));

        }
    }


    QString filename2=fileDialog->getSaveFileName();
    if(filename.isEmpty())
    {

    }
    else
    {
        if(! ui->hist_2->savePng(filename2) ) //保存图像
        {
            QMessageBox::information(NULL,
                Histogram::tr("Failed to save the image"),
                Histogram::tr("Failed to save the image!"));

        }
    }
}
