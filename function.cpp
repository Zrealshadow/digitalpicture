#include "function.h"
#define Pi 3.14159
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

int isvalid(int t){
    int ans;
    if(t>255){
        ans=255;
    }
    else if(t<0){
        ans=0;
    }
    else
        ans=t;
    return ans;
}

int NonLinear_sin(double x,const double c,int maxy){
    double t;
    t=1.0+sin(c*Pi*(x/maxy-1/2))/sin(Pi/2*c);
//    qDebug()<<"t"<<t;
//    qDebug()<<c*Pi*(x/maxy-1/2);
    return (int)(maxy/2*t);
}

int NonLinear_tan(double x,const double c,int maxy){
    double t;
    t=1.0+tan(c*Pi*(x/maxy-1/2))/tan(Pi/2*c);
    return (int)(maxy/2*t);
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
     QString path=fileDialog->getOpenFileName();
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

QImage* func::func_bright_dim(QImage *img,const double a,const int b){
    QImage *new_img=new QImage(img->width(),img->height(),img->format());
    for(int y=0;y<img->height();y++){
        QRgb *line=(QRgb *)img->scanLine(y);
        for(int x=0;x<img->width();x++){
            int red=isvalid(qRed(line[x])*a+b);
            int green=isvalid(qGreen(line[x])*a+b);
            int blue=isvalid(qBlue(line[x])*a+b);
            new_img->setPixel(x,y,qRgb(red,green,blue));
        }
    }
    return new_img;
}

QImage * func::func_profile(QImage *img,const bool ff,const double c ){
    QImage *new_img=new QImage(img->width(),img->height(),img->format());
    int maxy=0;
    for(int y=0;y<img->height();y++){
        QRgb * line=(QRgb*)img->scanLine(y);
        for(int x=0;x<img->width();x++){
            int average=(qRed(line[x])+qGreen(line[x])+qBlue(line[x]))/3;
            if(average>maxy)
                maxy=average;
        }
    }
    qDebug()<<"maxy"<<maxy;
    for(int y=0;y<img->height();y++){
        QRgb*line=(QRgb*)img->scanLine(y);
        for(int x=0;x<img->width();x++){
            double average=(qRed(line[x])+qGreen(line[x])+qBlue(line[x]))/3;
            int ans=0;
            if(ff){
                ans=NonLinear_sin(average,c,maxy);
            }
            else{
                ans=NonLinear_tan(average,c,maxy);
            }

            new_img->setPixel(x,y,qRgb(ans,ans,ans));
        }
    }
    return new_img;
}

QImage* func::func_equal(QImage *img){
    QImage *new_img=new QImage(img->width(),img->height(),img->format());

    int miny=256,maxy=0;
    int size=img->height()*img->width();
    QVector<double> vlist(256);
    for(int y=0;y<img->height();y++){
        QRgb* line=(QRgb*)img->scanLine(y);
        for(int x=0;x<img->width();x++){
            int v=(qRed(line[x])+qGreen(line[x])+qBlue(line[x]))/3;
            vlist[v]+=1;
            if(v>maxy)
                maxy=v;
            if(v<miny)
                miny=v;
        }
    }
    for(int i=miny;i<=maxy;i++){
        vlist[i]=vlist[i]/size;
        if(i!=miny)
            vlist[i]=vlist[i]+vlist[i-1];
    }
    QVector<int> trans_list(256);
    for(int i=miny;i<=maxy;i++){
        trans_list[i]=(int)(vlist[i]*(256-1));
    }

    for(int y=0;y<img->height();y++){
        QRgb* line=(QRgb*)img->scanLine(y);
        for(int x=0;x<img->width();x++){
            int v=(qRed(line[x])+qGreen(line[x])+qBlue(line[x]))/3;
            int tv=trans_list[v];
            new_img->setPixel(x,y,qRgb(tv,tv,tv));
        }
    }

    return new_img;
}
