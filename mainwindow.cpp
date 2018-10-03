#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "QDialog"
#include "QString"
#include "QMessageBox"
#include "QDebug"
#include "stdio.h"
#include "iostream"
#include "sstream"
#include "function.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QImage *temp=new QImage;
    QString path="../digitalprocess/asset/temp.png";
    if(!(temp->load(path))){
        QMessageBox::information(this,tr("Fail"),tr("fail to open the picture"));
        delete temp;
    }
    ui->temp->setScaledContents(true);
    ui->temp->setPixmap(QPixmap::fromImage(*temp));
    ui->temp_2->setScaledContents(true);
    ui->temp_2->setPixmap(QPixmap::fromImage(*temp));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//*----------------------------------------------------------*


QImage *img;
QImage * new_img;

void MainWindow::on_input_clicked()
{
            img=func::func_input();
            ui->input_img->setScaledContents(true);
            ui->input_img->setPixmap(QPixmap::fromImage(*img));
            ui->img_x->clear();
            ui->img_y->clear();
            ui->line_x->clear();
            ui->line_y->clear();
            ui->trans_img->clear();
            ui->img_x->insert(QString::number(img->width(),10));
            ui->img_y->insert(QString::number(img->height(),10));

}





void MainWindow::on_trans_clicked()
{
    QString pix_x=ui->line_x->text();
    QString pix_y=ui->line_y->text();
    new_img=func::func_sampling(img,pix_x,pix_y);
    ui->trans_img->setScaledContents(true);
    ui->trans_img->setPixmap(QPixmap::fromImage(*new_img));
}



void MainWindow::on_save_clicked()
{
    func::func_save(new_img);
}


void MainWindow::on_grey_clicked()
{
            QString s_grey=ui->Gray->text();
            new_img=func::func_quantify(img,s_grey);
            ui->trans_img_2->setScaledContents(true);
            ui->trans_img_2->setPixmap(QPixmap::fromImage(*new_img));
}


void MainWindow::on_input_3_clicked()
{
    img=func::func_input();
    ui->Gray->clear();
    ui->input_img_2->setScaledContents(true);
    ui->input_img_2->setPixmap(QPixmap::fromImage(*img));

}

void MainWindow::on_save_3_clicked()
{
      func::func_save(new_img);
}




void MainWindow::on_input_4_clicked()
{
    img=func::func_input();
    ui->input_img_3->setScaledContents(true);
    ui->input_img_3->setPixmap(QPixmap::fromImage(*img));
}

void MainWindow::on_save_4_clicked()
{
    func::func_save(new_img);
}


void MainWindow::on_bmp2txt_clicked()
{

}
