#include "../include/indicatorwidget.h"
#include "../UI_Module/ui_indicatorwidget.h"
#include "qboxlayout.h"
#include "qdialog.h"
#include <QMessageBox>

indicatorwidget::indicatorwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::indicatorwidget),
    buttonGroup(new QButtonGroup(this)),
    infoLabel(new QLabel(this))/*,
    infoDialog(new QDialog(this))*/
{
    ui->setupUi(this);
    infoLabel->setVisible(false);
    // Connect the clicked signal of the information button to the slot
    connect(ui->infoButton, &QPushButton::clicked, this, &indicatorwidget::infoButtonClicked);

    buttonGroup->addButton(ui->infoButton);
    connect(buttonGroup, &QButtonGroup::buttonClicked, this, &indicatorwidget::onButtonGroupClicked);
    setIndicatorName("Indicator 1");
    setInfoText("This is the information for indicator 1");

    // infoDialog = new QDialog(this);
    // infoDialog->setWindowTitle("Indicator Information");
    // QVBoxLayout *layout = new QVBoxLayout(infoDialog);
    // layout->addWidget(infoLabel);
    // infoDialog->setLayout(layout);
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
    infoLabel->setVisible(ui->infoButton->isChecked());
    infoLabel->setText(infoText);
    // infoDialog->show();
    QMessageBox msgBox;
    msgBox.setWindowTitle("Indicator Information");
    msgBox.setText(infoText);
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setStyleSheet("QMessageBox { background-color: white; color: black; }");
    msgBox.exec();
    qDebug() << "Info text:" << infoText;
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
