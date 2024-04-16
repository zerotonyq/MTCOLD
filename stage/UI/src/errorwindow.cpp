#include "../include/errorwindow.h"
#include "../UI_Module/ui_errorwindow.h"

errorWindow::errorWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::errorWindow)
{
    // this->setWindowFlags(Qt::CustomizeWindowHint);
    ui->setupUi(this);

    // this->setAttribute(Qt::WA_DeleteOnClose);
}

errorWindow::~errorWindow()
{
    delete ui;
}
