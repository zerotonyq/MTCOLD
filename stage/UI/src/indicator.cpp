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
#include <QDebug>
#include <iostream>
#include "../include/indicatorwidget.h"

QDialog* dialog = nullptr;

indicator::indicator(Core *core_, QWidget *parent)
    : core(core_)
    , QDialog(parent)
    , ui(new Ui::indicator),
    buttonGroup(new QButtonGroup(this))
{

    ui->setupUi(this);
    connect(activeIndicator, &indicatorwidget::maWhenIndicatorOff, errorwindow, &errorWindow::addErrorOfOff);


    connect(core, &Core::getIndicatorStatisticPacket, this, [=](const sIndicatorStatisticsPack& statisticPack){
        SerialNumber = statisticPack.indicatorData.serialNumber;
        type = statisticPack.indicatorData.type;
        power = statisticPack.indicatorData.power;
        color = statisticPack.indicatorData.color;
        current_ma = statisticPack.indicatorData.current_ma;
        reserve = statisticPack.indicatorData.reserve;
        error_code = statisticPack.indicatorData.error_code;

        QFile file(":/indicator_template.html");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

        QTextStream in(&file);
        QString htmlTemplate = in.readAll();
        file.close();

        QString newInfoText = htmlTemplate.arg(currentIndicatorNumber)
                                  .arg(SerialNumber)
                                  .arg(color == 0 ? "#D8BF65" : (color  == 1 ? "#379100" : "#8A0000"))
                                  .arg(color == 0 ? "желтый" : (color  == 1 ? "зеленый" : "красный"))
                                  //.arg()
                                  .arg(current_ma);
        if (current_ma > 1){
            emit ma_exceeded(current_ma, currentIndicatorNumber);
        }

        ui -> labelInfo -> setText(newInfoText);
        ui->labelInfo->show();
        ui->label->hide();
        ui->label_3->hide();
    });



    connect(core, &Core::getIndicatorsQuantityPacket, this, [=](const sIndicatorsCountPack& indicatorsCountPack) {
        currentIndicatorsQuantity = indicatorsCountPack.indicatorsCount;

    });

    QTimer *updateTimer = new QTimer(this);
    connect(updateTimer, &QTimer::timeout, this, &indicator::updateIndicatorInfo);
    updateTimer->start(1000);

    QTimer *updateQuantity = new QTimer(this);
    connect(updateQuantity, &QTimer::timeout,this, &indicator::updateQuantity);
    updateQuantity->start(10000);

    ui->labelInfo->hide();

    installEventFilter(this);

    QButtonGroup *buttonGroup = new QButtonGroup(this);
    QLabel *indicatorCountLabel = new QLabel(this);
    m_indicatorManager = new IndicatorManager(buttonGroup, indicatorCountLabel, this);
    
    
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

        emit onValueChanged(currentIndicatorsQuantity);

    }

    QWidget::showEvent(event);
}

void indicator::onInfoTextChanged(quint32 currentNumber, indicatorwidget *indicator)
{

    activeIndicator = indicator;
    currentIndicatorNumber = currentNumber;
    core->getIndicatorStat(currentIndicatorNumber);

    if (m_activeIndicatorWidget && m_activeIndicatorWidget != sender()) {

        m_activeIndicatorWidget->showInfoButton();
        m_activeIndicatorWidget = nullptr;
    }
    m_activeIndicatorWidget = qobject_cast<indicatorwidget *>(sender());
}

void indicator::onValueChanged(quint32 newValue)
{

    while (ui->verticalLayout->count() > 0) {
        QLayoutItem *item = ui->verticalLayout->takeAt(0);
        delete item->widget();
        delete item;
    }


    for (int i = 1; i <= newValue; ++i) {
        QFile file(":/indicator_template.html");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

        QTextStream in(&file);
        QString htmlTemplate = in.readAll();
        file.close();

        std::cout << "vvv " << current_ma << std::endl;
        indicatorwidget *activeIndicator_ = new indicatorwidget(core, errorwindow, current_ma, i, this);
        activeIndicator_->setIndicatorName(QString("Индикатор № %1").arg(i));
        activeIndicator_->setFixedSize(335, 80);
        connect(activeIndicator_, &indicatorwidget::infoTextChanged, this, &indicator::onInfoTextChanged);

        ui->verticalLayout->addWidget(activeIndicator_);


    }

    ui->indiccount->setFont(QFont("Trebuchet MS", 24));
    ui->indiccount->setText(QString("%1").arg(newValue));
    QSpacerItem *verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);
    ui->verticalLayout->addItem(verticalSpacer);


}
void indicator::updateIndicatorInfo() {

    if(m_activeIndicatorWidget && m_activeIndicatorWidget != sender()){
        core->getIndicatorStat(currentIndicatorNumber);
    }

}

void indicator::updateQuantity(){
    core->getIndicatorsQuantity();
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

    restartWindow = new restart(core, this);
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

    connect(this, &indicator::ma_exceeded, errorwindow, &errorWindow::addErrorOfExceeded);


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

void indicator::on_restart_clicked()
{

    QWidget::close();
    indicator newIndicator(core);
    newIndicator.currentIndicatorsQuantity = currentIndicatorsQuantity;
    newIndicator.setModal(true);
    newIndicator.exec();
}

