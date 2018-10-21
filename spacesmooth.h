#ifndef SPACESMOOTH_H
#define SPACESMOOTH_H

#include <QWidget>
#include <QLabel>
namespace Ui {
class Spacesmooth;
}

class Spacesmooth : public QWidget
{
    Q_OBJECT

public:
    explicit Spacesmooth(QWidget *parent = nullptr);
    ~Spacesmooth();
    QLabel *fig_spacesmooth;
private slots:


    void on_smooth_average_clicked();

    void on_smooth_middle_clicked();

    void on_smooth_kllinear_clicked();

private:
    Ui::Spacesmooth *ui;
};

#endif // SPACESMOOTH_H
