#include "../include/macaddress.h"
#include "../UI_Module/ui_macaddress.h"

macaddress::macaddress(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::macaddress)
{
    ui->setupUi(this);

    ui->current_device_address->setPlaceholderText("e0:db:55:a9:0c");

    ui->connected_device_address->setPlaceholderText("50:46:5d:6e:8c:20");
}

macaddress::~macaddress()
{
    delete ui;
}
