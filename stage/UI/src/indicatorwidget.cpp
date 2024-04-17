#include "../include/indicatorwidget.h"
#include "../UI_Module/ui_indicatorwidget.h"
#include "qboxlayout.h"
#include "qdialog.h"
#include <QMessageBox>

indicatorwidget::indicatorwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::indicatorwidget),
    buttonGroup(new QButtonGroup(this)),
    infoLabel(new QLabel(this))
{
    ui->setupUi(this);
    infoLabel->setVisible(false);
    // Connect the clicked signal of the information button to the slot
    connect(ui->infoButton, &QPushButton::clicked, this, &indicatorwidget::infoButtonClicked);

    buttonGroup->addButton(ui->infoButton);
    connect(buttonGroup, &QButtonGroup::buttonClicked, this, &indicatorwidget::onButtonGroupClicked);
    setIndicatorName("Indicator 1");

    infoDialog = new QDialog(this);
    infoDialog->setWindowTitle("Indicator Information");
    QVBoxLayout *layout = new QVBoxLayout(infoDialog);
    layout->addWidget(infoLabel);
    infoDialog->setLayout(layout);
}

indicatorwidget::~indicatorwidget()
{
    delete ui;
}

void indicatorwidget::setIndicatorName(const QString &name)
{
    ui->indicatorWidget->setText(name);
}

void indicatorwidget::infoButtonClicked()
{
    infoLabel->setVisible(ui->infoButton->isChecked());
    infoDialog->show();
    QMessageBox::information(this, "Indicator Information", infoLabel->text());
}

void indicatorwidget::onButtonGroupClicked(QAbstractButton *button)
{
    // Hide the QLabel for all other indicators when a button is clicked
    for (QAbstractButton *b : buttonGroup->buttons()) {
        if (b!= button) {
            indicatorwidget *iw = qobject_cast<indicatorwidget *>(b->parent());
            if (iw) {
                iw->infoLabel->setVisible(false);
            }
        }
    }
    infoLabel->setVisible(ui->infoButton->isChecked());
}
