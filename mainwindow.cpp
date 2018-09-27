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
    QFileDialog *fileDialog=new QFileDialog(this);
    fileDialog->setWindowTitle(tr("open file"));
    fileDialog->setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog->setFileMode(QFileDialog::AnyFile);
    fileDialog->setViewMode(QFileDialog::Detail);

    fileDialog->setGeometry(500,300,1000,600);
    fileDialog->setDirectory("..");
    fileDialog->selectNameFilter(tr("Image Files(*.png *.bmp *.jpg *.tif *.GIF)"));

    img=new QImage();

    if(fileDialog->exec()==QDialog::Accepted){
        QString path=fileDialog->selectedFiles()[0];
        if(path.isEmpty()){

        }
        else{

            if(!(img->load(path))){
               QMessageBox::information(this,tr("Fail"),tr("fail to open the picture"));
                delete img;
                return;
            }
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

    }
}

bool isDigitString(QString src){
    std::string s=src.toStdString();
    std::istringstream iss(s);
    int num;
    iss>>num;
    qDebug()<<num;
    if(num==0)
        return true;
    else
        return false;
}


void average(int x,int y,int dx,int dy,QImage *img,QImage *new_image){
    int rsum=0,gsum=0,bsum=0;
    for(int j=0;j<dy;j++){
        QRgb *line=(QRgb *)img->scanLine(y+j);
        for(int i=0;i<dx;i++)
        {
            rsum+=qRed(line[i+x]);
            bsum+=qBlue(line[i+x]);
            gsum+=qGreen(line[i+x]);
        }
    }

    for(int j=0;j<dy;j++){
        for (int i=0;i<dx;i++)
        {
            new_image->setPixel(x+i,y+j,qRgb(rsum/dx/dy,gsum/dx/dy,bsum/dx/dy));
        }
    }

}

void MainWindow::on_trans_clicked()
{

    
    QString pix_x=ui->line_x->text();
    QString pix_y=ui->line_y->text();
    new_img=new QImage(img->width(),img->height(),img->format());
    if(isDigitString(pix_x)||isDigitString(pix_y)){
        QMessageBox::information(this,tr("Fail"),tr("input format is error!"));
        return;
    }
    else{
        int npix_x=pix_x.toInt();
        int npix_y=pix_y.toInt();       
        int x_size=img->width()%npix_x==0?img->width()/npix_x:img->width()/npix_x+1;
        int y_size=img->height()%npix_y==0?img->height()/npix_y:img->height()/npix_y+1;

//        qDebug()<<x_size<<y_size<<endl;
        for(int y=0;y<img->height();){
            for(int x=0;x<img->width();){
                if(y+y_size<img->height()){
                    if(x+x_size<img->width())
                    {
//                        qDebug()<<x<<y<<1<<endl;
                        average(x,y,x_size,y_size,img,new_img);
                        x+=x_size;
                    }
                    else{
//                        qDebug()<<x<<y<<2<<endl;
                        average(x,y,1,y_size,img,new_img);
                        x+=1;
                    }

                }
                else{
                    if(x+x_size<img->width())
                    {
//                        qDebug()<<x<<y<<3<<endl;
                        average(x,y,x_size,1,img,new_img);
                        x+=x_size;
                    }
                    else{
//                        qDebug()<<x<<y<<4<<endl;
                        average(x,y,1,1,img,new_img);
                        x+=1;
                    }

                }
            }
            if(y+y_size<img->height())
                y+=y_size;
            else
                y+=1;
        }
        ui->trans_img->setScaledContents(true);
        ui->trans_img->setPixmap(QPixmap::fromImage(*new_img));
    }

}



void MainWindow::on_save_clicked()
{
    QFileDialog * fileDialog=new QFileDialog(this);
    fileDialog->setWindowTitle(tr("save As"));
    fileDialog->setAcceptMode(QFileDialog::AcceptSave);
    fileDialog->setFileMode(QFileDialog::AnyFile);
    fileDialog->setViewMode(QFileDialog::Detail);
    fileDialog->setGeometry(500,300,1000,600);
    fileDialog->setDirectory("..");
    fileDialog->selectNameFilter(tr("Image Files(*.png *.bmp *.jpg *.tif *.GIF)"));
    QString filename=fileDialog->getSaveFileName(this);
    if(filename.isEmpty())
    {
        return;
    }
    else
    {
        if(! ( new_img->save(filename) ) ) //保存图像
        {
            QMessageBox::information(this,
                tr("Failed to save the image"),
                tr("Failed to save the image!"));
            return;
        }
    }

}

int Greytrans(int grey,int pixel){
    int k=256/grey;
    int ans=0;
    for(int i=0;i<grey;i++){
        if((i+1)*k>pixel){
            ans=i*k+k/2;
            break;
        }
        else
            continue;
    }
    return ans;
}
void MainWindow::on_grey_clicked()
{

        QImage * Grey_img=new QImage(img->width(),img->height(),img->format());


        QString s_grey=ui->Gray->text();
        if(isDigitString(s_grey)){
            QMessageBox::information(this,tr("Fail"),tr("input format is error!"));
            return;
        }
        else{
            int grey=s_grey.toInt();
            for(int y=0;y<Grey_img->height();y++){
                QRgb *line=(QRgb *)img->scanLine(y);
                for(int x=0;x<Grey_img->width();x++){
                    int average=Greytrans(grey,(qRed(line[x])+qGreen(line[x])+qBlue(line[x]))/3);
                    Grey_img->setPixel(x,y,qRgb(average,average,average));
                }
            }
        }
        ui->trans_img->setScaledContents(true);
        ui->trans_img->setPixmap(QPixmap::fromImage(*Grey_img));
}



















