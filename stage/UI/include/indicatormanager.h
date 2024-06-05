    #ifndef INDICATORMANAGER_H
    #define INDICATORMANAGER_H

    #include <QObject>
    #include <QVBoxLayout>
    #include <QButtonGroup>
    #include <QLabel>
    #include "../../Core/include/core.h"
    #include "indicatorwidget.h"

    class IndicatorManager : public QObject
    {
        Q_OBJECT

    public:
        explicit IndicatorManager(QButtonGroup *buttonGroup, QLabel *indicatorCountLabel, QWidget *indicatorCentralWidget);
        ~IndicatorManager();

        IndicatorManager(Core *core): core(core){};

    public slots:
        void addIndicatorWidget(QWidget *indicatorWidget);

    private:
        Core *core;

        QVBoxLayout *m_layout;
    };

    #endif // INDICATORMANAGER_H
