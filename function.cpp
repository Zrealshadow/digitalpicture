#include "function.h"
/*-----------------------------------------------*/

bool isDigitString(QString src){
    std::string s=src.toStdString();
    std::istringstream iss(s);
    int num;
    iss>>num;
//    qDebug()<<num;
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


/*---------------------------------------------------*/

void func::func_save(QImage *img){
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
        if(! ( img->save(filename) ) ) //保存图像
        {
            QMessageBox::information(NULL,
                MainWindow::tr("Failed to save the image"),
                MainWindow::tr("Failed to save the image!"));

        }
    }
}

QImage * func::func_input(){
    QImage *img=new QImage();
    QFileDialog *fileDialog=new QFileDialog();
    fileDialog->setWindowTitle(MainWindow::tr("open file"));
    fileDialog->setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog->setFileMode(QFileDialog::AnyFile);
    fileDialog->setViewMode(QFileDialog::Detail);

    fileDialog->setGeometry(500,300,1000,600);
    fileDialog->setDirectory("..");
    fileDialog->selectNameFilter(MainWindow::tr("Image Files(*.png *.bmp *.jpg *.tif *.GIF)"));


    if(fileDialog->exec()==QDialog::Accepted){
        QString path=fileDialog->selectedFiles()[0];
        if(path.isEmpty()){

        }
        else{
//            qDebug()<<2;
//            qDebug()<<(img->load(path));
//            qDebug()<<2;
            if(!(img->load(path))){
               QMessageBox::information(NULL,MainWindow::tr("Fail"),MainWindow::tr("fail to open the picture"));
                delete img;

            }
            else
                return img;
            }
    }
}

QImage* func::func_quantify(QImage *img,QString s_grey){
    QImage *new_img=new QImage(img->width(),img->height(),img->format());

    if(isDigitString(s_grey)){
        QMessageBox::information(NULL,MainWindow::tr("Fail"),MainWindow::tr("input format is error!"));

    }
    else{
        int grey=s_grey.toInt();
        for(int y=0;y<new_img->height();y++){
            QRgb *line=(QRgb *)img->scanLine(y);
            for(int x=0;x<new_img->width();x++){
                int average=Greytrans(grey,(qRed(line[x])+qGreen(line[x])+qBlue(line[x]))/3);
                new_img->setPixel(x,y,qRgb(average,average,average));
            }
        }
        return new_img;
    }

}

QImage* func::func_sampling(QImage *img,QString pix_x,QString pix_y){

    QImage *new_img=new QImage(img->width(),img->height(),img->format());
    if(isDigitString(pix_x)||isDigitString(pix_y)){
        QMessageBox::information(NULL,MainWindow::tr("Fail"),MainWindow::tr("input format is error!"));
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
        return new_img;
    }

}

QImage *func::func_bmp2txt_one(QImage *img,int k){
    QImage *new_img=new QImage(img->width(),img->height(),img->format());
    QImage *grey_img=new QImage(img->width(),img->height(),img->format());
    grey_img=func::func_quantify(img,"256");
    for(int y=0;y<new_img->height();y++){
        QRgb *line=(QRgb *)img->scanLine(y);
        for(int x=0;x<new_img->width();x++){
            int value=qRed(line[x]);


            int ff=(value>>(8-k))&1;
//            if(x==2&&y==6){
//               value=2;
//               ff=(value>>1)&1;
//               qDebug()<<ff;
//            }
            if(ff==1){
//                qDebug()<<ff;
                new_img->setPixel(x,y,qRgb(255,255,255));
            }

            else{
//                qDebug()<<ff;
                new_img->setPixel(x,y,qRgb(0,0,0));
            }

        }
    }
    return new_img;
}

QImage * func::func_threshhold(QImage *img,QString s_t){
    QImage *new_img=new QImage(img->width(),img->height(),img->format());

    if(isDigitString(s_t)){
        QMessageBox::information(NULL,MainWindow::tr("fail"),MainWindow::tr("input format is error"));
    }
    else{
        int th=s_t.toInt();
        for(int y=0;y<img->height();y++){
            QRgb *line=(QRgb *)img->scanLine(y);
            for(int x=0;x<img->width();x++){
                int average=(qRed(line[x])+qGreen(line[x])+qBlue(line[x]))/3;
                if(average>th){
                    new_img->setPixel(x,y,qRgb(255,255,255));
                }
                else{
                    new_img->setPixel(x,y,qRgb(0,0,0));
                }
            }
        }
    }
    return new_img;
}

QHash<QString,double>func::func_cal(QImage *img){
    double mean,pixels,mid;
    double stdev;
    std::vector<int> v(0);
    for(int y=0;y<img->height();y++){
        QRgb *line=(QRgb *)img->scanLine(y);
        for(int x=0;x<img->width();x++){
             int average=(qRed(line[x])+qGreen(line[x])+qBlue(line[x]))/3;
             v.push_back(average);
        }
    }
    double sum=std::accumulate(std::begin(v),std::end(v),0.0);
    pixels=v.size();
    mean=sum/v.size();
    double accum=0.0;
    std::for_each (std::begin(v), std::end(v), [&](const double d) {
        accum  += (d-mean)*(d-mean);
    });
    stdev=sqrt(accum/(v.size()-1));
    sort(v.begin(),v.begin()+v.size());
    mid=v[v.size()/2];

    QHash<QString,double>map;
    map.insert("Mean",mean);
    map.insert("Pixels",pixels);
    map.insert("Mid",mid);
    map.insert("Stdev",stdev);

    return map;
}

QVector<double> func::func_pixmap(QImage *img){
    QVector<double> map(256);
    for(int y=0;y<img->height();y++){
        QRgb *line=(QRgb*)img->scanLine(y);
        for(int x=0;x<img->width();x++){
            int average=(qRed(line[x])+qGreen(line[x])+qBlue(line[x]))/3;
            map[average]=map[average]+1;
        }
    }
    return map;
}

//QImage* func::func_painter(std::vector<int> count,QImage *img){
//    QPainter *p=new QPainter();
//    p->setBrush(QBrush(QColor(121,121,121)));
//    p->drawRect(0,0,img->width(),img->height());

//    p->setBrush(QBrush(QColor(255,255,255)));
//    p->drawRect(0,0,img->width(),img->height());
//    std::vector<int> sortcount=count;
//    sort(sortcount.begin(),sortcount.end());
//    int maxcount=sortcount[sortcount.size()-1];

//    QImage *new_img=new QImage(img->width(),img->height(),img->format());

//    new_img->fill(qRgb(255,255,255));
//    p->translate(0,new_img->height());

//    p->drawLine(0,0,100,100);

//    int wid=new_img->width();
//    int hei=new_img->height();

//    p->drawLine(10,-10,wid-10,-10);
//    p->drawLine(10,-10,10,-hei+10);

//    float xstep=float(wid-20)/255;
//    float ystep=float(hei-20)/maxcount;

//    for(int i=0;i<256;i++){
//        if(i!=255){
//            QColor color(i,255-i,0);
//            p->setBrush(color);
//            p->setPen(color);

//            p->drawRect(10+i*xstep,-10,xstep,-10-ystep*count[i]);


//        }

//        if(i%32==0||i==255){
//            p->drawText(QPointF(10+(i-0.5)*xstep,0),QString::number(i));
//        }
//    }

//   return new_img;
//}
