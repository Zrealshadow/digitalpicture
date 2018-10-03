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
namespace func {
void func_save(QImage *image);
QImage * func_input();
QImage* func_sampling(QImage *image,QString pix_x,QString pix_y);
QImage* func_quantify(QImage *image,QString s_grey);
QImage* func_bmp2txt(QImage *image,int i);
}

#endif // FUNCTION_H
