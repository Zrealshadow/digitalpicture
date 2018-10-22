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
    __init__();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::__init__(){
    QImage *temp=new QImage;
    QString path="../digitalpictures/asset/temp.png";
    if(!(temp->load(path))){
        QMessageBox::information(this,tr("Fail"),tr("fail to open the picture"));
        delete temp;
    }
    ui->temp->setScaledContents(true);
    ui->temp->setPixmap(QPixmap::fromImage(*temp));
    ui->temp_2->setScaledContents(true);
    ui->temp_2->setPixmap(QPixmap::fromImage(*temp));
    ui->temp_3->setScaledContents(true);
    ui->temp_3->setPixmap(QPixmap::fromImage(*temp));
    ui->temp_plot->setScaledContents(true);
    ui->temp_plot->setPixmap(QPixmap::fromImage(*temp));
    ui->temp_hist->setScaledContents(true);
    ui->temp_hist->setPixmap(QPixmap::fromImage(*temp));
    ui->temp_point->setScaledContents(true);
    ui->temp_point->setPixmap(QPixmap::fromImage(*temp));


    ui->qcustomplotWidget->xAxis->setLabel("Gray");
    ui->qcustomplotWidget->yAxis->setLabel("Count");
    ui->qcustomplotWidget->xAxis->setRange(0,256);
    ui->qcustomplotWidget->xAxis->rescale(true);
    ui->qcustomplotWidget->yAxis->rescale(true);
    ui->qcustomplotWidget->xAxis2->setVisible(true);
    ui->qcustomplotWidget->xAxis2->setTickLabels(false);
    ui->qcustomplotWidget->yAxis2->setVisible(true);
    ui->qcustomplotWidget->yAxis2->setTickLabels(false);
}

bool MainWindow::input_isvalid(QImage *p){
    if(p==NULL){
        QMessageBox::information(this,tr("Fail"),tr("Your chose is wrong!"));
        return false;
    }
    else
        return true;
}
//*----------------------------------------------------------*

QImage *img;
QImage * new_img;
bool NonLinear_form=true;
const double bright_coef=1.2;
const double dim_coef=0.8;
const int bright_bias=0;
const int dim_bias=0;
const double NonLinear_coef=1.0;
void MainWindow::input_init(){
    ui->input_img->setScaledContents(true);
    ui->input_img->setPixmap(QPixmap::fromImage(*img));
    ui->trans_img->clear();

    ui->input_img_2->setScaledContents(true);
    ui->input_img_2->setPixmap(QPixmap::fromImage(*img));
    ui->trans_img_2->clear();

    ui->input_img_3->setScaledContents(true);
    ui->input_img_3->setPixmap(QPixmap::fromImage(*img));

    ui->input_img_plot->setScaledContents(true);
    ui->input_img_plot->setPixmap(QPixmap::fromImage(*img));
    ui->trans_img_plot->clear();

    ui->input_img_hist->setScaledContents(true);
    ui->input_img_hist->setPixmap(QPixmap::fromImage(*img));

    ui->input_img_point->setScaledContents(true);
    ui->input_img_point->setPixmap(QPixmap::fromImage(*img));
    ui->trans_img_point->clear();

    ui->fig_space->setPixmap(QPixmap::fromImage(*img));

}

QLabel* MainWindow::output_label(){
    return ui->fig_space;
}

//*--------------------------------slot--------------------------------------//
void MainWindow::on_input_clicked()
{

     img=func::func_input();
     if(input_isvalid(img)){
            input_init();
            ui->img_x->clear();
            ui->img_y->clear();
            ui->line_x->clear();
            ui->line_y->clear();

            ui->img_x->insert(QString::number(img->width(),10));
            ui->img_y->insert(QString::number(img->height(),10));
     }

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
    if(input_isvalid(img)){
        ui->Gray->clear();
        input_init();
    }

}

void MainWindow::on_save_3_clicked()
{
      func::func_save(new_img);
}

void MainWindow::on_input_4_clicked()
{
    img=func::func_input();
    if(input_isvalid(img)){
    input_init();
    }
}

void MainWindow::on_save_4_clicked()
{
    func::func_save(new_img);
}


void MainWindow::on_bmp2txt_clicked()
{
    for(int i=0;i<8;i++){
        new_img=func::func_bmp2txt_one(img,i+1);
        switch (i+1) {
            case 1:ui->sp_1->setScaledContents(true);ui->sp_1->setPixmap(QPixmap::fromImage(*new_img));break;
            case 2:ui->sp_2->setScaledContents(true);ui->sp_2->setPixmap(QPixmap::fromImage(*new_img));break;
            case 3:ui->sp_3->setScaledContents(true);ui->sp_3->setPixmap(QPixmap::fromImage(*new_img));break;
            case 4:ui->sp_4->setScaledContents(true);ui->sp_4->setPixmap(QPixmap::fromImage(*new_img));break;
            case 5:ui->sp_5->setScaledContents(true);ui->sp_5->setPixmap(QPixmap::fromImage(*new_img));break;
            case 6:ui->sp_6->setScaledContents(true);ui->sp_6->setPixmap(QPixmap::fromImage(*new_img));break;
            case 7:ui->sp_7->setScaledContents(true);ui->sp_7->setPixmap(QPixmap::fromImage(*new_img));break;
            case 8:ui->sp_8->setScaledContents(true);ui->sp_8->setPixmap(QPixmap::fromImage(*new_img));break;
        }
    }
}

void MainWindow::on_input_plot_clicked()
{
    img=func::func_input();
    if(input_isvalid(img))
        input_init();

}

void MainWindow::on_plot_2_clicked()
{
    ui->mean->clear();
    ui->mid->clear();
    ui->std->clear();
    ui->Pixels->clear();

    QString s_t=ui->Threshold->text();
    new_img=func::func_threshhold(img,s_t);
    QHash<QString,double> map=func::func_cal(img);

    ui->Pixels->insert(QString::number((int)map["Pixels"],10));
    ui->mean->insert(QString::number((int)map["Mean"],10));
    ui->mid->insert(QString::number((int)map["Mid"],10));
    ui->std->insert(QString::number(map["Stdev"],10,2));
    ui->trans_img_plot->setScaledContents(true);
    ui->trans_img_plot->setPixmap(QPixmap::fromImage(*new_img));
}

void MainWindow::on_save_plot_clicked()
{
        func::func_save(new_img);
}


void MainWindow::on_input_hist_clicked()
{

    img=func::func_input();
    if(input_isvalid(img))
        input_init();

}

void MainWindow::on_hist_clicked()
{
    ui->mean_hist->clear();
    ui->mid_hist->clear();
    ui->std_hist->clear();
    ui->Pixels_hist->clear();
    QHash<QString,double> map=func::func_cal(img);
    ui->Pixels_hist->insert(QString::number((int)map["Pixels"],10));
    ui->mean_hist->insert(QString::number((int)map["Mean"],10));
    ui->mid_hist->insert(QString::number((int)map["Mid"],10));
    ui->std_hist->insert(QString::number(map["Stdev"],10,2));


    QVector<double> datay=func::func_pixmap(img);
//    new_img=func::func_painter(map,img);
    int maxy=0;
    QVector<double>::iterator it;
    for(it=datay.begin();it!=datay.end();it++){
        if(*it>maxy)
            maxy=*it;
    }

    ui->qcustomplotWidget->clearGraphs();
    QVector<double> datax(256);
    for(int i=0;i<256;i++){
        datax[i]=i;
    }
//    qDebug()<<datax;
//    qDebug()<<datay;
    ui->qcustomplotWidget->xAxis->setLabel("Gray");
    ui->qcustomplotWidget->yAxis->setLabel("Count");
    ui->qcustomplotWidget->xAxis->setRange(0,270);
    ui->qcustomplotWidget->yAxis->setRange(0,maxy);



    QCPBars *bars=new QCPBars(ui->qcustomplotWidget->xAxis,ui->qcustomplotWidget->yAxis);
    bars->setData(datax,datay);
    bars->setPen(QColor(0,0,0));
    bars->setWidth(0.5);
    ui->qcustomplotWidget->setVisible(true);
    ui->qcustomplotWidget->replot();



}

void MainWindow::on_save_hist_clicked()
{
    QFileDialog * fileDialog=new QFileDialog();
    fileDialog->setWindowTitle(MainWindow::tr("save As"));
    fileDialog->setAcceptMode(QFileDialog::AcceptSave);
    fileDialog->setFileMode(QFileDialog::AnyFile);
    fileDialog->setViewMode(QFileDialog::Detail);
    fileDialog->setGeometry(500,300,1000,600);
    fileDialog->setDirectory("..");
    fileDialog->selectNameFilter(MainWindow::tr("Image Files(*.png *.bmp *.jpg *.tif *.GIF)"));
    QString filename=fileDialog->getSaveFileName();
    if(filename.isEmpty())
    {

    }
    else
    {
        if(! ui->qcustomplotWidget->savePng(filename) ) //保存图像
        {
            QMessageBox::information(NULL,
                MainWindow::tr("Failed to save the image"),
                MainWindow::tr("Failed to save the image!"));

        }
    }
}

void MainWindow::on_input_hist_point_clicked()
{
    img=func::func_input();
    if(input_isvalid(img)){
        new_img=img;
        input_init();
    }

}

void MainWindow::on_save_hist_point_clicked()
{
    func::func_save(new_img);
}



void MainWindow::on_bright_point_clicked()
{
    new_img=func::func_bright_dim(new_img,bright_coef,bright_bias);
    ui->trans_img_point->setScaledContents(true);
    ui->trans_img_point->setPixmap(QPixmap::fromImage(*new_img));

}

void MainWindow::on_dim_point_clicked()
{
    new_img=func::func_bright_dim(new_img,dim_coef,dim_bias);
    ui->trans_img_point->setScaledContents(true);
    ui->trans_img_point->setPixmap(QPixmap::fromImage(*new_img));
}

void MainWindow::on_show_histogram_point_clicked()
{
    hist_show=new Histogram(this);
    hist_show->setStyleSheet("background-color:black;");
    MainWindow::hist_show->show();
}

void MainWindow::on_profile_point_clicked()
{
    new_img=func::func_profile(new_img,NonLinear_coef,NonLinear_form);
    ui->trans_img_point->setScaledContents(true);
    ui->trans_img_point->setPixmap(QPixmap::fromImage(*new_img));
}



void MainWindow::on_equal_point_clicked()
{
    new_img=func::func_equal(img);
    ui->trans_img_point->setScaledContents(true);
    ui->trans_img_point->setPixmap(QPixmap::fromImage(*new_img));
}

void MainWindow::on_input_space_clicked()
{

    img=func::func_input();
    if(input_isvalid(img)){
        new_img=img;
        input_init();
    }
}

void MainWindow::on_space_zoom_clicked()
{
     Spacezoom *input_zoom=new Spacezoom();

     input_zoom->fig_spacezoom=ui->fig_space;
     input_zoom->show();


}

void MainWindow::on_space_move_clicked()
{
    Spacemove *input_move=new Spacemove();

    input_move->fig_spacemove=ui->fig_space;
    input_move->show();
}

void MainWindow::on_space_Flip_clicked()
{
    new_img=func::func_space_filp(new_img);
    ui->fig_space->setPixmap(QPixmap::fromImage(*new_img));
}

void MainWindow::on_space_Rotate_clicked()
{
    Spacerotate *input_rotate=new Spacerotate();

    input_rotate->fig_spacerotate=ui->fig_space;
    input_rotate->show();
}

void MainWindow::on_space_smooth_clicked()
{
    Spacesmooth *input_smooth=new Spacesmooth();

    input_smooth->fig_spacesmooth=ui->fig_space;
    input_smooth->show();
}

void MainWindow::on_space_sharpen_clicked()
{
   Spacesharpen *input_sharpen=new Spacesharpen();

   input_sharpen->fig_spacesharpen=ui->fig_space;
   input_sharpen->show();
}

void MainWindow::on_space_conv_clicked()
{
    Spaceconv *input_conv=new Spaceconv();
    input_conv->fig_spaceconv=ui->fig_space;
    input_conv->show();
}
