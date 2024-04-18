
#include "../include/indicatormanager.h"
#include "qcheckbox.h"
#include "qpushbutton.h"
#include <QAbstractButton>
#include <QFont>
#include <QFontMetrics>


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

    for (int i = m_layout->count(); i < count; ++i) {
        indicatorwidget *indicatorWidget = new indicatorwidget(m_indicatorCentralWidget);
        QString indicatorName = QString("Индикатор № %1").arg(i);
        indicatorWidget->setIndicatorName(indicatorName);

        indicatorWidget->setParent(m_indicatorCentralWidget);

        // Set up the toggle button
        QCheckBox *toggleButton = indicatorWidget->findChild<QCheckBox*>("toggle");
        connect(toggleButton, &QCheckBox::toggled, [toggleButton, i, this]() {
            if (toggleButton->isChecked()) {
                // Код обработки действий при включении кнопки
                core->turnOnIndicator(i);
            } else {
                // Код обработки действий при выключении кнопки
                core->turnOffIndicator(i);
            }
        });

        m_layout->addWidget(indicatorWidget);
    }

    m_indicatorCountLabel->setText(QString("Total Indicators: %1").arg(count));
}
