#include "../include/macaddress.h"
#include "../UI_Module/ui_macaddress.h"

macaddress::macaddress(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::macaddress)
{
    ui->setupUi(this);

    ui->current_device_address->setPlaceholderText("e0:db:55:a9:0c");
    ui->current_device_address->setStyleSheet("QLineEdit {"
                                                "   color: #FDFDFB;"  // Цвет основного текста
                                                "   font: 32pt 'random grotesque standard book';"
                                                "   border: none;"
                                                "}"
                                                "QLineEdit::placeholderText {"
                                                "   color: #FDFDFB;"
                                                "   font: 32pt 'random grotesque standard book';"
                                                "   border: none;"
                                                "}");

    ui->connected_device_address->setPlaceholderText("50:46:5d:6e:8c:20");
    ui->connected_device_address->setStyleSheet("QLineEdit {"
                                                "   color: #FDFDFB;"  // Цвет основного текста
                                                "   font: 32pt 'random grotesque standard book';"
                                                "   border: none;"
                                                "}"
                                                "QLineEdit::placeholderText {"
                                                "   color: #FDFDFB;"
                                                "   font: 32pt 'random grotesque standard book';"
                                                "   border: none;"
                                                "}");
}

macaddress::~macaddress()
{
    delete ui;
}
