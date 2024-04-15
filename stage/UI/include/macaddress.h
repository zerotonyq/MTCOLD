#ifndef MACADDRESS_H
#define MACADDRESS_H

#include <QWidget>

namespace Ui {
class macaddress;
}

class macaddress : public QWidget
{
    Q_OBJECT

public:
    explicit macaddress(QWidget *parent = nullptr);
    ~macaddress();

private:
    Ui::macaddress *ui;
};

#endif // MACADDRESS_H
