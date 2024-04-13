
#include "indicatormanager.h"
#include "qcheckbox.h"
#include "qpushbutton.h"
#include <QAbstractButton>
#include <QFont>
#include <QFontMetrics>

#include "indicatorwidget.h"

IndicatorManager::IndicatorManager(QButtonGroup *buttonGroup, QLabel *indicatorCountLabel, QWidget *parentWidget)
    : QObject(parentWidget) // Требуется инициализировать родительский QObject
    , m_buttonGroup(buttonGroup)
    , m_indicatorCountLabel(indicatorCountLabel)
{
    m_layout = new QVBoxLayout(parentWidget); // Инициализация QVBoxLayout с родительским виджетом
    // Другие инициализации и подключения сигналов
}

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
        // Создание контейнера для индикатора
        QWidget *indicatorContainer = new QWidget();

        // Создание вертикального лейаута для индикатора
        QVBoxLayout *mainLayout = new QVBoxLayout(indicatorContainer);

        // Создание горизонтального лейаута для кнопок индикатора
        QHBoxLayout *buttonLayout = new QHBoxLayout();

        // Создание и стилизация лейбла индикатора
        QLabel *indicatorLabel = new QLabel(QString("Indicator %0").arg(i));

        // Уменьшение ширины лейбла в два раза
        QFont font = indicatorLabel->font();
        QFontMetrics fm(font);

        int textWidth = fm.horizontalAdvance(indicatorLabel->text());
        int newWidth = 400;

        font.setPixelSize(fm.height()); // Сохраняем высоту шрифта без изменений
        indicatorLabel->setFont(font);
        indicatorLabel->setFixedWidth(newWidth);

        indicatorLabel->setStyleSheet("QLabel { height: 50px; border: 2px solid white; border-radius: 15px; padding: 5px; background-color: black; color: white; };");

        // Создание кнопки для отображения информации
        QPushButton *infoButton = new QPushButton("Info");
        infoButton->setStyleSheet("background-color: #4CAF50; color: white;");
        connect(infoButton, &QPushButton::clicked, this, [this, i](){
            // Действия по нажатию на кнопку Info
            // Например, показ дополнительной информации
        });


        // Создание кнопки для переключения состояния
        QCheckBox *toggleButton = new QCheckBox();
        toggleButton->setStyleSheet("QCheckBox::indicator { width: 60px; height: 80px; background-image: url(:/image/resources/img/info.png); }"
                                    "QCheckBox::indicator:checked { image: url(:/image/resources/img/on_new.jpg); background-image: url(:/image/resources/img/info.png); }"
                                    "QCheckBox::indicator:unchecked { image: url(:/image/resources/img/off_new.jpg); background-image: url(:/image/resources/img/info.png); }");
        connect(toggleButton, &QCheckBox::toggled, this, [toggleButton](){
            if (toggleButton->isChecked()) {
                // Действия при включении состояния
            } else {
                // Действия при выключении состояния
            }
        });

        // Добавление кнопок в лейаут
        buttonLayout->addWidget(infoButton);
        buttonLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum)); // Добавляем пустое пространство для выравнивания
        buttonLayout->addWidget(toggleButton);

        // Добавление элементов в главный вертикальный лейаут
        mainLayout->addWidget(indicatorLabel);
        mainLayout->addLayout(buttonLayout);

        // Добавление контейнера в общий лейаут
        m_layout->addWidget(indicatorContainer);
    }

    // Обновление отображаемого количества индикаторов
    m_indicatorCountLabel->setText(QString("Total Indicators: %1").arg(count));

}

// void IndicatorManager::updateIndicatorCount(int count)
// {
//     // Очистить текущие индикаторы
//     QLayoutItem *child;
//     while ((child = m_layout->takeAt(0)) != nullptr) {
//         delete child->widget();
//         delete child;
//     }

//     // Создать новые индикаторы
//     for (int i = 0; i < count; ++i) {
//         IndicatorWidget *indicatorWidget = new IndicatorWidget(QString("Индикатор №%0").arg(i));
//         m_layout->addWidget(indicatorWidget);
//     }

//     // Обновление отображаемого количества индикаторов
//     m_indicatorCountLabel->setText(QString("Total Indicators: %1").arg(count));
// }




void IndicatorManager::onButtonClicked(QAbstractButton* button)
{
    // Ваша обработка событий нажатия на кнопки с индикаторами
}



