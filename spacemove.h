#ifndef SPACEMOVE_H
#define SPACEMOVE_H

#include <QWidget>

namespace Ui {
class Spacemove;
}

class Spacemove : public QWidget
{
    Q_OBJECT

public:
    explicit Spacemove(QWidget *parent = nullptr);
    ~Spacemove();

private:
    Ui::Spacemove *ui;
};

#endif // SPACEMOVE_H
