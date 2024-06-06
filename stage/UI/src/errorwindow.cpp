#include "../include/errorwindow.h"
#include "../UI_Module/ui_errorwindow.h"

errorWindow::errorWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::errorWindow)
{
    ui->setupUi(this);
    layout = new QVBoxLayout(this);
    textEdit = new QTextEdit(this);
    layout->addWidget(textEdit);
    setLayout(layout);
}

errorWindow::~errorWindow()
{
    delete ui;
}

void errorWindow::addErrorOfExceeded(quint32 ma, quint32 indicator){
    textEdit->append(QString("Error: ma exceeded 1 for indicator #%1 , current value: %2").arg(indicator).arg(ma));
}

void errorWindow::addErrorOfOff(quint32 ma, quint32 indicator){
    textEdit->append(QString("Error: ma is greater than zero when the indicator #%1 is off, current value: %2").arg(indicator).arg(ma));
}
