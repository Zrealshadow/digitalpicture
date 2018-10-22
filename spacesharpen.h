#ifndef SPACESHARPEN_H
#define SPACESHARPEN_H

#include <QWidget>
#include <QLabel>
namespace Ui {
class Spacesharpen;
}

class Spacesharpen : public QWidget
{
    Q_OBJECT

public:
    QLabel * fig_spacesharpen;
    explicit Spacesharpen(QWidget *parent = nullptr);
    ~Spacesharpen();

private slots:
    void on_sharpen_roberts_clicked();

    void on_sharpen_laplace_clicked();

    void on_sharpen_sobel_clicked();

    void on_sharpen_prewitt_clicked();

private:
    Ui::Spacesharpen *ui;
};

#endif // SPACESHARPEN_H
