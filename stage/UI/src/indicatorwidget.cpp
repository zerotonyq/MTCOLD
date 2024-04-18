#include "../include/indicatorwidget.h"
#include "../UI_Module/ui_indicatorwidget.h"
#include "qboxlayout.h"
#include "qdialog.h"

indicatorwidget::indicatorwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::indicatorwidget),
    buttonGroup(new QButtonGroup(this))
{
    ui->setupUi(this);
    connect(ui->infoButton, &QPushButton::clicked, this, &indicatorwidget::infoButtonClicked);
}

indicatorwidget::~indicatorwidget()
{
    delete ui;
}

void indicatorwidget::setIndicatorName(const QString &name)
{
    ui->indicatorWidget->setText(name);
}

void indicatorwidget::setInfoText(const QString &text)
{
    infoText = text;
}


void indicatorwidget::infoButtonClicked()
{
    hideInfoButton();
    emit infoTextChanged(infoText);
}

void indicatorwidget::hideInfoButton()
{
    ui->infoButton->hide();
}

void indicatorwidget::showInfoButton()
{
    ui->infoButton->show();
}

void indicatorwidget::onButtonGroupClicked(QAbstractButton *button)
{
    for (QAbstractButton *b : buttonGroup->buttons()) {
        if (b != button) {
            indicatorwidget *iw = qobject_cast<indicatorwidget *>(b->parent());
            if (iw) {
                iw->showInfoButton();
                emit iw->infoTextChanged("");
            }
        }
    }
    if (!ui->infoButton->isChecked()) {
        hideInfoButton();
    }
}

