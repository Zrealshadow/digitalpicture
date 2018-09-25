#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "QDialog"
#include "QString"
#include "QMessageBox"
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
    ui->temp->setPixmap(QPixmap::fromImage(*temp));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_input_clicked()
{
    QFileDialog *fileDialog=new QFileDialog(this);
    fileDialog->setWindowTitle(tr("open file"));
    fileDialog->setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog->setFileMode(QFileDialog::AnyFile);
    fileDialog->setViewMode(QFileDialog::Detail);

    fileDialog->setGeometry(500,300,1000,600);
    fileDialog->setDirectory("..");
    fileDialog->selectNameFilter(tr("Image Files(*.png *.bmp *.jpg *.tif *.GIF)"));

    if(fileDialog->exec()==QDialog::Accepted){
        QString path=fileDialog->selectedFiles()[0];
        if(path.isEmpty()){

        }
        else{
            QImage *img=new QImage;
            if(!(img->load(path))){
               QMessageBox::information(this,tr("Fail"),tr("fail to open the picture"));
                delete img;
                return;
            }
            ui->input_img->setPixmap(QPixmap::fromImage(*img));
        }

    }
}

void MainWindow::on_trans_clicked()
{
    
}

void MainWindow::on_save_clicked()
{
    
}
