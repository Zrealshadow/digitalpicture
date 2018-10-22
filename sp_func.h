#ifndef SP_FUNC_H
#define SP_FUNC_H
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
#include "cmath"
#include "algorithm"
#include "QPainter"
#include "QVector"
typedef std::vector<std::vector<int>>  filter_operate;
namespace sp_func {
QImage* func_zoom_in_out(QImage *img,double coef);

int func_doublelinear_trans(QImage *img,double x,double y,QString color);

QRgb func_nearby_trans(QImage* img,double x,double y);
QImage *func_zoom_nearby(QImage *img,double coef);

QImage *func_move(QImage *img,int dx,int dy);

QImage *func_rotate_DoubleLinear(QImage *img,int c_x,int c_y,double angle);

QImage *func_rotate_Nearby(QImage *img,int c_x,int c_y,double angle);

QImage *func_smooth_average(QImage *img);
QImage *func_smooth_middle(QImage *img);
QImage *func_smooth_klinear(QImage *img,int k);

QImage *func_filter_trans(QImage *img,std::vector<std::vector<int>> filter);
int cal_filter(QImage *img,std::vector<std::vector<int>>filter,int x,int y);
filter_operate struct_filter(int x,int y,QString s);
}

#endif // SP_FUNC_H
