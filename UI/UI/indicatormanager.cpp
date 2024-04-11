
#include "indicatormanager.h"
#include "qcheckbox.h"
#include "qpushbutton.h"
#include <QAbstractButton>

IndicatorManager::IndicatorManager(QButtonGroup *buttonGroup, QLabel *indicatorCountLabel, QWidget *parentWidget)
    : QObject(parentWidget) // Требуется инициализировать родительский QObject
    , m_buttonGroup(buttonGroup)
    , m_indicatorCountLabel(indicatorCountLabel)
{
    m_layout = new QVBoxLayout(parentWidget); // Инициализация QVBoxLayout с родительским виджетом
    // Другие инициализации и подключения сигналов
}

// void IndicatorManager::updateIndicatorCount(int count)
// {
//     // Очистить текущие индикаторы
//     for (int i = m_layout->count() - 1; i >= 0; --i) {
//         QLayoutItem *item = m_layout->itemAt(i);
//         QWidget *widget = item->widget();
//         m_layout->removeWidget(widget);
//         delete widget;
//     }

//     // Загрузить дизайн из .ui файла
//     QFile file("../UI/indicatormanager.ui");
//     file.open(QFile::ReadOnly);
//     QUiLoader loader;
//     QWidget *uiWidget = loader.load(&file, this);

//     // Добавить загруженный дизайн в m_layout
//     m_layout->addWidget(uiWidget);

//     // Обновление отображаемого количества индикаторов
//     m_indicatorCountLabel->setText(QString("Общее количество индикаторов: %1").arg(count));
// }

void IndicatorManager::updateIndicatorCount(int count)
{
    // Очистить текущие индикаторы
    QLayoutItem *child;
    while ((child = m_layout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    // Создать новые индикаторы
    for (int i = 0; i < count; ++i) {
        QWidget *indicatorContainer = new QWidget();
        QHBoxLayout *indicatorLayout = new QHBoxLayout(indicatorContainer);

        QLabel *indicatorLabel = new QLabel(QString("Индикатор №%0").arg(i));
        indicatorLabel->setStyleSheet("styles for indicator"); // Установите стили для лейбла

        QPushButton *infoButton = new QPushButton("Info");
        connect(infoButton, &QPushButton::clicked, this, [this, i](){
            // Обработка нажатия на кнопку info
            // Возможно, вызов окна с информацией или другие действия
        });

        // QCheckBox *toggle = new QCheckBox();
        // connect(toggle, &QCheckBox::toggled, this, [this, i](bool checked){
        //     // Обработка изменения состояния тогла
        // });

        QString toggleButtonStyleOn = "QPushButton { background-color: green; color: white; border-radius: 10px; }";
        QString toggleButtonStyleOff = "QPushButton { background-color: red; color: white; border-radius: 10px; }";

        QPushButton *toggleButton = new QPushButton("OFF");
        toggleButton->setStyleSheet(toggleButtonStyleOff);
        connect(toggleButton, &QPushButton::clicked, [toggleButton, toggleButtonStyleOn, toggleButtonStyleOff]() {
            if(toggleButton->text() == "OFF") {
                toggleButton->setText("ON");
                toggleButton->setStyleSheet(toggleButtonStyleOn);
            } else {
                toggleButton->setText("OFF");
                toggleButton->setStyleSheet(toggleButtonStyleOff);
            }
        });

        m_layout->addWidget(indicatorLabel);
        m_layout->addWidget(infoButton);
        m_layout->addWidget(toggleButton);
    }

    // Обновление отображаемого количества индикаторов
    m_indicatorCountLabel->setText(QString("Total Indicators: %1").arg(count));

}


void IndicatorManager::onButtonClicked(QAbstractButton* button)
{
    // Ваша обработка событий нажатия на кнопки с индикаторами
}



