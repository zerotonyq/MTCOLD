
#include "indicatormanager.h"
#include "qcheckbox.h"
#include "qpushbutton.h"
#include <QAbstractButton>
#include <QFont>
#include <QFontMetrics>

#include "indicatormanager.h"


IndicatorManager::IndicatorManager(QButtonGroup *buttonGroup, QLabel *indicatorCountLabel, QWidget *indicatorCentralWidget)
    : QObject(indicatorCentralWidget)
    , m_buttonGroup(buttonGroup)
    , m_indicatorCountLabel(indicatorCountLabel)
    , m_indicatorCentralWidget(indicatorCentralWidget)
{
    m_layout = new QVBoxLayout(m_indicatorCentralWidget);
    m_layout->setContentsMargins(0, 0, 0, 0);
    QSpacerItem *verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_layout->addItem(verticalSpacer);
    connect(buttonGroup, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(onButtonClicked(QAbstractButton*)));
}

IndicatorManager::~IndicatorManager()
{
    delete m_layout;
}
void IndicatorManager::addIndicatorWidget(QWidget *indicatorWidget)
{
    m_layout->addWidget(indicatorWidget);
}

void IndicatorManager::updateIndicatorCount(int count) {

    QLayoutItem *child;
    while ((child = m_layout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    for (int i = 0; i < count; ++i) {

        indicatorwidget *indicatorWidget = new indicatorwidget(m_indicatorCentralWidget); // Установка родительского виджета
        QString indicatorName = QString("Индикатор № %1").arg(i);
        indicatorWidget->setIndicatorName(indicatorName);

        // Set up the toggle button
        QCheckBox *toggleButton = indicatorWidget->findChild<QCheckBox*>("toggle");
        connect(toggleButton, &QCheckBox::toggled, [toggleButton](){
            if (toggleButton->isChecked()) {

            } else {

            }
        });

        m_layout->addWidget(indicatorWidget);
    }

    m_indicatorCountLabel->setText(QString("Total Indicators: %1").arg(count));
}


// void IndicatorManager::onButtonClicked(QAbstractButton* button)
// {
//     // Ваша обработка событий нажатия на кнопки с индикаторами
// }



