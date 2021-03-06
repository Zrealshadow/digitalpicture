#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <QWidget>
#include <hist_func.h>
namespace Ui {
class Histogram;
}

class Histogram : public QWidget
{
    Q_OBJECT

public:
    explicit Histogram(QWidget *parent = nullptr);
    ~Histogram();

private slots:
    void on_quit_clicked();

    void on_pushButton_clicked();

private:
    Ui::Histogram *ui;
    void __init__();
};

#endif // HISTOGRAM_H
