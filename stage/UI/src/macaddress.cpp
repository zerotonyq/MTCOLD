#include "../include/macaddress.h"
#include "../UI_Module/ui_macaddress.h"

macaddress::macaddress(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::macaddress)
{
    ui->setupUi(this);
}

macaddress::~macaddress()
{
    delete ui;
}
