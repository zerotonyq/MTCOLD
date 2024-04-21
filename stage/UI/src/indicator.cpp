#include "../include/indicator.h"
#include "../include/errorwindow.h"
#include "../include/macaddress.h"
#include "qbuttongroup.h"
#include "qevent.h"

#include "../include/restart.h"
#include "../UI_Module/ui_indicator.h"
#include "../include/indicatormanager.h"

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QEvent>
#include <QButtonGroup>
#include <QGraphicsDropShadowEffect>
#include <QTimer>
#include "../include/indicatorwidget.h"

QDialog* dialog = nullptr;

indicator::indicator(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::indicator),
    buttonGroup(new QButtonGroup(this))
{
    ui->setupUi(this);

    ui->labelInfo->hide();

    installEventFilter(this);

    quint32 sii = static_cast<quint32>(count);
    scount = QString::number(sii);
    ui->indiccount->setText(scount);

    QButtonGroup *buttonGroup = new QButtonGroup(this);
    QLabel *indicatorCountLabel = new QLabel(this);
    m_indicatorManager = new IndicatorManager(buttonGroup, indicatorCountLabel, this);

    connect(this, SIGNAL(valueChanged(int)), this, SLOT(onValueChanged(int)));

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &indicator::errorFlashing);
    timer->start(1000);
}

indicator::~indicator() {
    delete ui;
}

void indicator::showEvent(QShowEvent *event)
{
    if (event->type() == QEvent::Show) {

        int newValue = 8;
        emit onValueChanged(newValue);
    }

    QWidget::showEvent(event);
}

void indicator::onInfoTextChanged(const QString &text)
{
    ui -> labelInfo -> setText(text);
    ui->labelInfo->show();
    ui->label->hide();
    ui->label_3->hide();

    if (m_activeIndicatorWidget && m_activeIndicatorWidget != sender()) {
        m_activeIndicatorWidget->showInfoButton();
        m_activeIndicatorWidget = nullptr;
    }
    m_activeIndicatorWidget = qobject_cast<indicatorwidget *>(sender());
}

void indicator::onValueChanged(int newValue)
{
    while (ui->verticalLayout->count() > 0) {
        QLayoutItem *item = ui->verticalLayout->takeAt(0);
        delete item->widget();
        delete item;
    }

    QFile file(":/indicator_template.html");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    QString htmlTemplate = in.readAll();
    file.close();

    for (int i = 1; i <= newValue; ++i) {
        indicatorwidget* indicator = new indicatorwidget(this);
        indicator->setIndicatorName(QString("Индикатор № %1").arg(i));
        indicator->setFixedSize(330, 80);

        QString infoText = htmlTemplate.arg(i)
                               .arg(i)
                               .arg(i % 2 == 0 ? "#379100" : "#8A0000")
                               .arg(i % 2 == 0 ? "зелёный" : "красный")
                               .arg(0.572 * i);
        indicator->setInfoText(infoText);
        ui->verticalLayout->addWidget(indicator);
        connect(indicator, &indicatorwidget::infoTextChanged, this, &indicator::onInfoTextChanged);
    }

    ui->indiccount->setFont(QFont("Trebuchet MS", 24));
    ui->indiccount->setText(QString("%1").arg(newValue));
    QSpacerItem *verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);
    ui->verticalLayout->addItem(verticalSpacer);
}

void indicator::errorFlashing() {
    static bool isRed = false;
    QString basicStyle = "QPushButton {"
                         "font: 400 16px 'Trebuchet MS', sans-serif;"
                         "color: #FDFDFB;"
                         "background: #353535;"
                         "border: none;"
                         "}";

    QString hoverStyle = "QPushButton:hover {"
                         "text-decoration: underline;"
                         "}";

    if (isRed) {
        // Возвращаем к стандартному стилю
        ui->mistakes->setStyleSheet(basicStyle + hoverStyle);
    } else {
        // Изменяем на красный с эффектом свечения
        ui->mistakes->setStyleSheet(basicStyle +
                                    "QPushButton { color: #8A0000; box-shadow: 0 0 10px red; }" +
                                    hoverStyle);
    }
    isRed = !isRed;
}

void indicator::on_build_clicked()
{
    if (restartWindow != nullptr && restartWindow->isVisible())
    {
        restartWindow->close();
        return;
    }

    restartWindow = new restart(this);
    restartWindow->setWindowFlags(Qt::CustomizeWindowHint);

    int offsetX = 30;
    int offsetY = 45;
    restartWindow->move(QPoint(offsetX, offsetY));
    restartWindow->show();
}


void indicator::on_mistakes_clicked()
{
    if (errorwindow != nullptr && errorwindow->isVisible())
    {
        errorwindow->close();
        return;
    }

    errorwindow = new errorWindow(this);
    errorwindow->setWindowFlags(Qt::CustomizeWindowHint);

    int offsetX = 455;
    int offsetY = 45;
    errorwindow->move(QPoint(offsetX, offsetY));
    errorwindow->show();
}


void indicator::on_macAddress_clicked()
{
    if (macAddress != nullptr && macAddress->isVisible())
    {
        macAddress->close();
        return;
    }

    macAddress = new macaddress(this);
    macAddress->setWindowFlags(Qt::CustomizeWindowHint);

    int offsetX = 650;
    int offsetY = 45;
    macAddress->move(QPoint(offsetX, offsetY));
    macAddress->show();
}
