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
    ui->temp->setScaledContents(true);
    ui->temp->setPixmap(QPixmap::fromImage(*temp));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//*----------------------------------------------------------*


QImage *img=new QImage;

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

            if(!(img->load(path))){
               QMessageBox::information(this,tr("Fail"),tr("fail to open the picture"));
                delete img;
                return;
            }
            ui->input_img->setScaledContents(true);
            ui->input_img->setPixmap(QPixmap::fromImage(*img));
            ui->img_x->insert(QString::number(img->width(),10));
            ui->img_y->insert(QString::number(img->height(),10));
        }

    }
}

bool isDigitString(QString src){
    std::string s=src.toStdString();
    int i;
    for(i=0;i<s.length();i++)
        if(s[i]>'9'&&s[i]<'0')
            break;

    if(i==s.length())
        return true;
    else
        return false;
}

int chosesize(int in,int out){
    int i=1;
    while(i*out<in){
        i++;
    }
    return i;
}

QList<int>average(int x,int dx,int dy,QList<QRgb *>lines){
    int rsum=0,gsum=0,bsum=0;
    QList<int> pixes;
    for(int i=0;i<dy;i++){
        for(int j=0;j<dx;j++){
            QRgb *line=lines.at(i);
            for(int m=x;m<x+dx;m++){
               rsum+=qRed(line[m]);
               gsum+=qGreen(line[m]);
               bsum+=qBlue(line[m]);
            }

        }
    }
    pixes.append(rsum/dx/dy);
    pixes.append(gsum/dx/dy);
    pixes.append(bsum/dx/dy);
    return pixes;
}

void MainWindow::on_trans_clicked()
{
//    QImage * new_img=new QImage(img->width(),img->height(),QImage::Format_ARGB32);

//    for(int y=0;y<new_img->height();y++){
//        QRgb *line=(QRgb *)img->scanLine(y);

//        for(int x=0;x<new_img->width();x++){
//            int average=(qRed(line[x])+qGreen(line[x])+qBlue(line[x]))/3;
//            new_img->setPixel(x,y,qRgb(average,average,average));
//        }
//    }
//    ui->trans_img->setScaledContents(true);
//    ui->trans_img->setPixmap(QPixmap::fromImage(*new_img));
    
    QString pix_x=ui->line_x->text();
    QString pix_y=ui->line_y->text();

    if(false){
        QMessageBox::information(this,tr("Fail"),tr("input format is error!"));
        return;
    }
    else{
        int npix_x=pix_x.toInt();
        int npix_y=pix_y.toInt();       
        int x_size=chosesize(img->width(),npix_x);
        int y_size=chosesize(img->height(),npix_y);
        int n_x=img->width()/x_size;
        int n_y=img->height()/y_size;

         QImage * new_img=new QImage(npix_x,npix_y,QImage::Format_ARGB32);


        for(int i=0,ic=0;ic<npix_y;ic++){
            QList<QRgb *> lines;
            if(i<n_x){
                for(int k=0;k<n_y;k++){
                    QRgb * line=(QRgb *)img->scanLine(i+k);
                    lines.append(line);
            }
                for(int j=0,jc=0;jc<npix_x;jc++){
                    if(j<n_y){
                        QList<int> pixes=average(j,x_size,y_size,lines);
                        j+=x_size;
                        new_img->setPixel(jc,ic,qRgb(pixes.at(0),pixes.at(1),pixes.at(2)));
                    }
                    else{
                        QList<int> pixes=average(j,1,y_size,lines);
                        j+=1;
                        new_img->setPixel(jc,ic,qRgb(pixes.at(0),pixes.at(1),pixes.at(2)));
                    }

                }
                i+=y_size;
            }
            else{
                for(int k=0;k<1;k++){
                    QRgb * line=(QRgb *)img->scanLine(i+k);
                    lines.append(line);
                }
                for(int j=0,jc=0;jc<npix_x;jc++){
                    if(j<n_y){
                        QList<int> pixes=average(j,x_size,1,lines);
                        j+=x_size;
                        new_img->setPixel(jc,ic,qRgb(pixes.at(0),pixes.at(1),pixes.at(2)));
                    }
                    else{
                        QList<int> pixes=average(j,1,1,lines);
                        j+=1;
                        new_img->setPixel(jc,ic,qRgb(pixes.at(0),pixes.at(1),pixes.at(2)));
                    }

                }
                i+=1;
                }
            }
        ui->trans_img->setScaledContents(true);
        ui->trans_img->setPixmap(QPixmap::fromImage(*new_img));
    }

}



void MainWindow::on_save_clicked()
{
    
}
