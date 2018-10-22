#ifndef SPACECONV_H
#define SPACECONV_H

#include <QWidget>
#include <QLabel>
typedef std::vector<std::vector<int>>  filter_operate;
namespace Ui {
class Spaceconv;
}

class Spaceconv : public QWidget
{
    Q_OBJECT

public:
    QLabel *fig_spaceconv;
    explicit Spaceconv(QWidget *parent = nullptr);
    ~Spaceconv();

private slots:
    void on_spaceconv_transfer_clicked();

private:
    Ui::Spaceconv *ui;

};

#endif // SPACECONV_H
