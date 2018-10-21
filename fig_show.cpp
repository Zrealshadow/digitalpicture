#include "fig_show.h"
#include "ui_fig_show.h"

Fig_show::Fig_show(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Fig_show)
{
    ui->setupUi(this);
}

Fig_show::~Fig_show()
{
    delete ui;
}
