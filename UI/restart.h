#ifndef RESTART_H
#define RESTART_H

#include <QDialog>

namespace Ui {
class restart;
}

class restart : public QDialog
{
    Q_OBJECT

public:
    explicit restart(QWidget *parent = nullptr);
    ~restart();

private:
    Ui::restart *ui;

protected:
    void mousePressEvent(QMouseEvent* event) override;
};

#endif // RESTART_H
