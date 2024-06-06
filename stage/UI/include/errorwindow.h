#ifndef ERRORWINDOW_H
#define ERRORWINDOW_H

#include "qboxlayout.h"
#include <QDialog>
#include <QTextEdit>

namespace Ui {
class errorWindow;
}

class errorWindow : public QDialog {
    Q_OBJECT

public:
    explicit errorWindow(QWidget *parent = nullptr);
    ~errorWindow();

public slots:
    void addErrorOfExceeded(quint32 ma_value, quint32 indicator);
    void addErrorOfOff(quint32 ma_valur, quint32 indicator);

private:
    Ui::errorWindow *ui;

    QTextEdit *textEdit;
    QVBoxLayout *layout;
};

#endif // ERRORWINDOW_H
