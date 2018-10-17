#ifndef SPACEMOVE_H
#define SPACEMOVE_H

#include <QWidget>
#include <QLabel>
namespace Ui {
class Spacemove;
}

class Spacemove : public QWidget
{
    Q_OBJECT

public:
    QLabel *fig_spacemove;
    explicit Spacemove(QWidget *parent = nullptr);
    ~Spacemove();

private slots:
    void on_spacemove_move_clicked();

    void on_spacemove_quit_clicked();

private:
    Ui::Spacemove *ui;
};

#endif // SPACEMOVE_H
