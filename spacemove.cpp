#include "spacemove.h"
#include "ui_spacemove.h"

Spacemove::Spacemove(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Spacemove)
{
    ui->setupUi(this);
}

Spacemove::~Spacemove()
{
    delete ui;
}
