#ifndef FIG_SHOW_H
#define FIG_SHOW_H

#include <QWidget>

namespace Ui {
class Fig_show;
}

class Fig_show : public QWidget
{
    Q_OBJECT

public:
    explicit Fig_show(QWidget *parent = nullptr);
    ~Fig_show();

private:
    Ui::Fig_show *ui;
};

#endif // FIG_SHOW_H
