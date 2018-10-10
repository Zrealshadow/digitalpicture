#ifndef HIST_FUNC_H
#define HIST_FUNC_H
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
#include "qcustomplot.h"

namespace hist_func {
QCustomPlot * plot_histogram(QCustomPlot *g,QImage *img);

}
#endif // HIST_FUNC_H
