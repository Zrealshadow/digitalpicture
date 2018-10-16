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
#include "math.h"
#include "algorithm"
#include "QPainter"
#include "QVector"

namespace sp_func {
QImage* func_zoom_in_out(QImage *img,double coef);

int func_zoom_trans(QImage *img,double x,double y,QString color);
}
#endif // SP_FUNC_H
