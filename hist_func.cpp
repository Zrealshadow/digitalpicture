#include "hist_func.h"

QCustomPlot * hist_func::plot_histogram(QCustomPlot *g,QImage *img){
       QVector<double> datay(256);
       for(int y=0;y<img->height();y++){
           QRgb *line=(QRgb*)img->scanLine(y);
           for(int x=0;x<img->width();x++){
               int average=(qRed(line[x])+qGreen(line[x])+qBlue(line[x]))/3;
               datay[average]=datay[average]+1;
          }
       }
       int maxy=0;
       QVector<double>::iterator it;
       for(it=datay.begin();it!=datay.end();it++){
           if(*it>maxy)
               maxy=*it;
       }

       QVector<double> datax(256);
       for(int i=0;i<256;i++){
           datax[i]=i;
       }

       g->xAxis2->setVisible(true);
       g->xAxis2->setTickLabels(false);
       g->yAxis2->setVisible(true);
       g->yAxis2->setTickLabels(false);
       g->xAxis->setLabel("Gray");
       g->yAxis->setLabel("Count");
       g->xAxis->setRange(0,270);
       g->yAxis->setRange(0,maxy);
       g->xAxis->rescale(true);
       g->yAxis->rescale(true);
       g->xAxis->rescale(true);
       g->yAxis->rescale(true);
       g->xAxis2->setVisible(true);
       g->xAxis2->setTickLabels(false);
       g->yAxis2->setVisible(true);
       g->yAxis2->setTickLabels(false);

       QCPBars *bar=new QCPBars(g->xAxis,g->yAxis);
       bar->setData(datax,datay);
       bar->setPen(QColor(0,0,0));
       bar->setWidth(0.5);
       g->setVisible(true);
       g->replot();
       return g;
}
