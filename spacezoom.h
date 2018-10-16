#ifndef SPACEZOOM_H
#define SPACEZOOM_H

#include <QWidget>
#include <qlabel.h>
namespace Ui {
class Spacezoom;
}

class Spacezoom : public QWidget
{
    Q_OBJECT

public:
    QLabel* fig_spacezoom;
    explicit Spacezoom(QWidget *parent = nullptr);
    ~Spacezoom();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::Spacezoom *ui;

};

#endif // SPACEZOOM_H
