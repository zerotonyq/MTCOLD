#include "indicatorwidget.h"
#include "ui_indicatorwidget.h"

indicatorwidget::indicatorwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::indicatorwidget)
{
    ui->setupUi(this);
}

indicatorwidget::~indicatorwidget()
{
    delete ui;
}

void indicatorwidget::setIndicatorName(const QString &name)
{
    ui->indicatorWidget->setText(name);
}
