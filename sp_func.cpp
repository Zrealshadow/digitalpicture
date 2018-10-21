#include "sp_func.h"
#include "spacezoom.h"
int sp_func::func_doublelinear_trans(QImage *img,double xx,double yy,QString color){
    int x,y;
    x=(int)xx;
    y=(int)yy;
    int a,b,c,d;
    x=x+1<=img->width()-1?x:img->width()-2;
    y=y+1<=img->height()-1?y:img->height()-2;
    QHash<QString,int> map;
    map.insert("red",1);
    map.insert("green",2);
    map.insert("blue",3);
    int h=map[color];
    switch(h){
    case 1:{
        a=qRed(img->pixel(x,y));
        b=qRed(img->pixel(x+1,y));
        c=qRed(img->pixel(x,y+1));
        d=qRed(img->pixel(x+1,y+1));

    }break;
    case 2:{
        a=qGreen(img->pixel(x,y));
        b=qGreen(img->pixel(x+1,y));
        c=qGreen(img->pixel(x,y+1));
        d=qGreen(img->pixel(x+1,y+1));

    }break;


    case 3:{
        a=qBlue(img->pixel(x,y));
        b=qBlue(img->pixel(x+1,y));
        c=qBlue(img->pixel(x,y+1));
        d=qBlue(img->pixel(x+1,y+1));
        }break;
    default:{
        QMessageBox::information(NULL,Spacezoom::tr("Fail"),Spacezoom::tr("the type is error"));
        return -1;
    }
    }
    double value=(xx-x)*(yy-y)*c+(xx-x)*(y+1-yy)*a+(x+1-xx)*(yy-y)*d+(x+1-xx)*(y+1-yy)*b;
    return (int)value;
}

QRgb sp_func::func_nearby_trans(QImage *img,double xx,double yy){
     int x,y;
     x=xx-(int)xx>0.5?(int)xx+1:(int)xx;
     y=yy-(int)yy>0.5?(int)yy+1:(int)yy;
     x=x>img->width()-1?img->width()-1:x;
     y=y>img->height()-1?img->height()-1:y;
     if(x>img->width()-1||x<0||y<0||y>img->height()-1){
         return qRgb(0,0,0);
     }
     else{
          return img->pixel(x,y);
     }

}

QImage * sp_func::func_zoom_in_out(QImage *img ,double coef){
       int w,h;
       w=(int)(img->width()*coef);
       h=(int)(img->height()*coef);
//       qDebug()<<"w"<<w<<endl<<"h"<<h;
//       qDebug()<<"wi"<<img->width()<<"\n"<<img->height();
       QImage *new_img=new QImage (w,h,img->format());
       for(int y=0;y<h;y++){
           for(int x=0;x<w;x++){
               double xx,yy;
               xx=(double)x/coef;
               yy=(double)y/coef;
               int r=sp_func::func_doublelinear_trans(img,xx,yy,"red");
               int g=sp_func::func_doublelinear_trans(img,xx,yy,"green");
               int b=sp_func::func_doublelinear_trans(img,xx,yy,"blue");
               new_img->setPixel(x,y,qRgb(r,g,b));
           }
       }
       return new_img;
}

QImage * sp_func::func_zoom_nearby(QImage *img,double coef){
    int w,h;
    w=(int)(img->width()*coef);
    h=(int)(img->height()*coef);

    QImage *new_img=new QImage (w,h,img->format());

    for(int y=0;y<h;y++){
        for(int x=0;x<w;x++){
            double xx,yy;
            xx=(double)x/coef;
            yy=(double)y/coef;   
            QRgb v=sp_func::func_nearby_trans(img,xx,yy);
            new_img->setPixel(x,y,v);
        }
    }

    return new_img;
}


QImage *sp_func::func_move(QImage *img,int dx,int dy){
    QImage *new_img=new QImage(img->width(),img->height(),img->format());
    for(int y=0;y<img->height();y++){
        for(int x=0;x<img->width();x++){
            int p_x,p_y;
            p_x=x-dx;
            p_y=y-dy;
            if(p_x>img->width()-1||p_x<0||p_y<0||p_y>img->height()-1){
                new_img->setPixel(x,y,qRgb(0,0,0));
            }
            else{
                QRgb v=img->pixel(p_x,p_y);
                new_img->setPixel(x,y,v);
            }
        }
    }
    return new_img;
}

QImage * sp_func::func_rotate_DoubleLinear(QImage *img,int cx,int cy,double angle){
    QImage *new_img=new QImage(img->width(),img->height(),img->format());

    for(int y=0;y<img->height();y++){
        for(int x=0;x<img->width();x++){
            double xx,yy;
            xx=(x-cx)*cos(angle)+(y-cy)*sin(angle)+cx;
            yy=(y-cy)*cos(angle)-(x-cx)*sin(angle)+cy;
            if(xx>img->width()-1||xx<0||yy>img->height()-1||yy<0){
                new_img->setPixel(x,y,qRgb(0,0,0));
            }
            else{
                int r,g,b;
                r=sp_func::func_doublelinear_trans(img,xx,yy,"red");
                g=sp_func::func_doublelinear_trans(img,xx,yy,"green");
                b=sp_func::func_doublelinear_trans(img,xx,yy,"blue");
                new_img->setPixel(x,y,qRgb(r,g,b));
            }
        }
    }
    return new_img;
}

QImage * sp_func::func_rotate_Nearby(QImage *img,int cx,int cy,double angle){
    QImage * new_img=new QImage(img->width(),img->height(),img->format());
    for(int y=0;y<img->height();y++){
        for(int x=0;x<img->width();x++){
            double xx,yy;
            xx=(x-cx)*cos(angle)+(y-cy)*sin(angle)+cx;
            yy=(y-cy)*cos(angle)-(x-cx)*sin(angle)+cy;
            if(xx>img->width()-1||xx<0||yy>img->height()-1||yy<0){
                new_img->setPixel(x,y,qRgb(0,0,0));
            }
            else{
                QRgb v;
                v=sp_func::func_nearby_trans(img,xx,yy);
                new_img->setPixel(x,y,v);
            }
        }
    }
    return new_img;
}

QImage * sp_func::func_smooth_average(QImage *img){
    QImage *new_img=new QImage(img->width(),img->height(),img->format());
    for(int y=0;y<img->height();y++){
        for(int x=0;x<img->width();x++){
            if(x<1 or x>img->width()-2 or y<1 or y>img->height()-2)
                new_img->setPixel(x,y,img->pixel(x,y));
            else{

                    std::vector<int> v(0);
                    for(int i=y-1;i<=y+1;i++){
                        for(int j=x-1;j<=x+1;j++){
                            QRgb color=img->pixel(j,i);
                            int value=(qRed(color)+qGreen(color)+qBlue(color))/3;
                            v.push_back(value);
                        }
                    }
                   int sum=std::accumulate(std::begin(v),std::end(v),0);
                   int mean=sum/v.size();
                   new_img->setPixel(x,y,qRgb(mean,mean,mean));
            }
        }
    }
    return new_img;
}

QImage *sp_func::func_smooth_middle(QImage *img){
    QImage *new_img=new QImage(img->width(),img->height(),img->format());

    for(int y=0;y<img->height();y++){
        for(int x=0;x<img->width();x++){
            if(x<1 or x>img->width()-2 or y<1 or y>img->height()-2)
                new_img->setPixel(x,y,img->pixel(x,y));
            else{

                std::vector<int> v(0);
                for(int i=y-1;i<=y+1;i++){
                    for(int j=x-1;j<=x+1;j++){
                        QRgb color=img->pixel(j,i);
                        int value=(qRed(color)+qGreen(color)+qBlue(color))/3;
                        v.push_back(value);
                    }
                }
                sort(v.begin(),v.end());
                int ans=v[v.size()/2];
                new_img->setPixel(x,y,qRgb(ans,ans,ans));
            }
        }
    }
    return new_img;
}

bool cmp(const QPair<int,int>a,QPair<int,int>b){
    return a.first<b.first;
}
QImage *sp_func::func_smooth_klinear(QImage *img,int k){
    QImage *new_img=new QImage(img->width(),img->height(),img->format());
    for(int y=0;y<img->height();y++){
        for(int x=0;x<img->width();x++){
            if(x<1 or x>img->width()-2 or y<1 or y>img->height()-2)
                new_img->setPixel(x,y,img->pixel(x,y));
            else{
                std::vector<QPair<int,int>> l(0);
                QRgb c=img->pixel(x,y);
                int v=(qRed(c)+qGreen(c)+qBlue(c))/3;
                for(int i=y-1;i<=y+1;i++)
                    for(int j=x-1;j<=x+1;j++){
                        QRgb color=img->pixel(j,i);
                        int value=(qRed(color)+qGreen(color)+qBlue(color))/3;
                        QPair<int,int> pair;
                        pair.first=abs(value-v);
                        pair.second=value;
                        l.push_back(pair);
                    }
                sort(l.begin(),l.end(),cmp);
                int sum=0;
                std::vector<QPair<int,int>>::iterator it=l.begin();
                for(int i=0;it!=l.end() && i<k;i++,it++){
                    sum+=(*it).second;
                }
                int ans=k>l.size()?sum/l.size():sum/k;
                if(x==y){
                    qDebug()<<l;
                    qDebug()<<ans;
                }
                new_img->setPixel(x,y,qRgb(ans,ans,ans));
            }

        }
    }
    return new_img;

}
