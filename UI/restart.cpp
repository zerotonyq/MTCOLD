#include "restart.h"
#include "ui_restart.h"
#include <QMouseEvent>


restart::restart(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::restart)
{
    this->setWindowFlags(Qt::CustomizeWindowHint);
    ui->setupUi(this);

    ui -> api_3 ->setPlaceholderText("192.168.100.167");
    ui -> api_2 ->setPlaceholderText("5001");

    this->setAttribute(Qt::WA_DeleteOnClose);
}

restart::~restart()
{
    delete ui;
}

void restart::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton && !childAt(event->pos()))
        close();
}

