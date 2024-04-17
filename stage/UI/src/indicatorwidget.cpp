#include "../include/indicatorwidget.h"
#include "../UI_Module/ui_indicatorwidget.h"
#include "qboxlayout.h"
#include "qdialog.h"

indicatorwidget::indicatorwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::indicatorwidget),
    buttonGroup(new QButtonGroup(this)),
    infoLabel(new QLabel(this)),
    infoDialog(new QDialog(this))
{
    ui->setupUi(this);
    infoLabel->setVisible(false);
    connect(ui->infoButton, &QPushButton::clicked, this, &indicatorwidget::infoButtonClicked);

    buttonGroup->addButton(ui->infoButton);
    connect(buttonGroup, &QButtonGroup::buttonClicked, this, &indicatorwidget::onButtonGroupClicked);
    setIndicatorName("Indicator 1");
    setInfoText("This is the information for indicator 1");

    infoDialog->setWindowTitle("Indicator Information");
    QLabel *infoLabel = new QLabel(infoDialog);
    infoLabel->setWordWrap(true);
    QVBoxLayout *layout = new QVBoxLayout(infoDialog);
    layout->addWidget(infoLabel);
    infoDialog->setLayout(layout);
    infoDialog->setStyleSheet("background-color: white;");
    infoDialog->resize(540, 570);
    infoDialog->move(440, 150);
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
\
void indicatorwidget::infoButtonClicked()
{
    infoLabel->setVisible(ui->infoButton->isChecked());
    QLabel *infoLabel = qobject_cast<QLabel*>(infoDialog->layout()->itemAt(0)->widget());
    infoLabel->setText(infoText + " " + QString::number(QObject::sender()->parent()->property("index").toInt()));
    infoDialog->show();
    qDebug() << "Info text:" << infoText;
}

void indicatorwidget::onButtonGroupClicked(QAbstractButton *button)
{
    for (QAbstractButton *b : buttonGroup->buttons()) {
        if (b!= button) {
            indicatorwidget *iw = qobject_cast<indicatorwidget *>(b->parent());
            if (iw) {
                iw->infoLabel->setVisible(false);
                iw->ui->infoButton->setChecked(false);
            }
        }
    }
    infoLabel->setVisible(ui->infoButton->isChecked());
}
