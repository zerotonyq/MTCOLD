#include "../include/indicatormanager.h"
#include "qcheckbox.h"
#include <QAbstractButton>
#include <QFont>
#include <QFontMetrics>

IndicatorManager::IndicatorManager(QButtonGroup *buttonGroup, QLabel *indicatorCountLabel, QWidget *indicatorCentralWidget)
    : QObject(indicatorCentralWidget){}

IndicatorManager::~IndicatorManager()
{
    delete m_layout;
}
void IndicatorManager::addIndicatorWidget(QWidget *indicatorWidget)
{
    m_layout->addWidget(indicatorWidget);
}

// не удаляю на всякий из-за тоглов и кора, ВИКА!!!!!!!!


//         QCheckBox *toggleButton = indicatorWidget->findChild<QCheckBox*>("toggle");
//         connect(toggleButton, &QCheckBox::toggled, [toggleButton, i, this]() {
//             if (toggleButton->isChecked()) {
//                 core->turnOnIndicator(i);
//             } else {
//                 core->turnOffIndicator(i);
// }
