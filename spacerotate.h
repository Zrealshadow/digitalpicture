#ifndef SPACEROTATE_H
#define SPACEROTATE_H

#include <QWidget>
#include <QLabel>
namespace Ui {
class Spacerotate;
}

class Spacerotate : public QWidget
{
    Q_OBJECT

public:
    QLabel * fig_spacerotate;
    explicit Spacerotate(QWidget *parent = nullptr);
    ~Spacerotate();

private slots:
    void on_rotate_doublelinear_clicked();

    void on_rotate_nearby_clicked();

private:
    Ui::Spacerotate *ui;
};

#endif // SPACEROTATE_H
