#ifndef ERRORWINDOW_H
#define ERRORWINDOW_H

#include <QDialog>

namespace Ui {
class errorWindow;
}

class errorWindow : public QDialog {
    Q_OBJECT

public:
    explicit errorWindow(QWidget *parent = nullptr);
    ~errorWindow();

private:
    Ui::errorWindow *ui;
};

#endif // ERRORWINDOW_H
