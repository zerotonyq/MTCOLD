#include "../include/indicatorwidget.h"
#include "../UI_Module/ui_indicatorwidget.h"
#include "qboxlayout.h"
#include "qdialog.h"

indicatorwidget::indicatorwidget(Core* core_, quint32 numberOfIndicator_, QWidget *parent) :
    core(core_),
    numberOfIndicator(numberOfIndicator_),
    QWidget(parent),
    ui(new Ui::indicatorwidget),
    buttonGroup(new QButtonGroup(this))
{
    ui->setupUi(this);
    connect(ui->infoButton, &QPushButton::clicked, this, &indicatorwidget::infoButtonClicked);
    connect(ui->toggle0_2,&QCheckBox::stateChanged, this, &indicatorwidget::toggleClicked);
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


void indicatorwidget::toggleClicked(int state)
{
    if (state == Qt::Checked){
        core->turnOnIndicator(numberOfIndicator);
        stateOfToggle = 1;
    } else {
        core->turnOffIndicator(numberOfIndicator);
        stateOfToggle = 0;
    }
}

void indicatorwidget::infoButtonClicked()
{
    hideInfoButton();
    emit infoTextChanged(numberOfIndicator, this);

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
            }
        }
    }
    if (!ui->infoButton->isChecked()) {
        hideInfoButton();
    }
}
