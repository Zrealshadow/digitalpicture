#ifndef FUNCTION_H
#define FUNCTION_H
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
#include "QImage"
#include "QHash"
#include "vector"
#include "math.h"
#include "algorithm"
#include "QPainter"
#include "QVector"
namespace func {

void func_save(QImage *image);

QImage * func_input();

QImage* func_sampling(QImage *image,QString pix_x,QString pix_y);

QImage* func_quantify(QImage *image,QString s_grey);

QImage* func_bmp2txt_one(QImage *image,int i);

QImage* func_threshhold(QImage *img,QString s_t);

QHash<QString,double>  func_cal(QImage *img);

QVector<double> func_pixmap(QImage *img);

//QImage* func_painter(std::vector<int> count,QImage * img);

}

#endif // FUNCTION_H
