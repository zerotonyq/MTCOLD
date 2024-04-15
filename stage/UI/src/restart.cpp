#include "../include/restart.h"
#include "../UI_Module/ui_restart.h"
#include <QMouseEvent>


restart::restart(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::restart)
{
    // this->setWindowFlags(Qt::CustomizeWindowHint);
    ui->setupUi(this);

    ui -> api_3 ->setPlaceholderText("192.168.100.167");

    ui -> api_2 ->setPlaceholderText("5001");

    // this->setAttribute(Qt::WA_DeleteOnClose);
}

restart::~restart()
{
    delete ui;
}



// void restart::mousePressEvent(QMouseEvent* event)
// {
//     if (event->button() == Qt::LeftButton && !childAt(event->pos()))
//         close();
// }

// В файле restart.h или restart.cpp

// bool restart::event(QEvent *event)
// {
//     if (event->type() == QEvent::MouseButtonPress) {
//         // Проверяем, было ли нажатие за пределами окна restart
//         QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
//         if (!ui->api_3->geometry().contains(mouseEvent->pos()) && !ui->api_2->geometry().contains(mouseEvent->pos())) {
//             close();
//         }
//     }

//     return QDialog::event(event); // Передаем событие в родительский класс для стандартной обработки
// }

void restart::on_restart_2_clicked()
{
    QString api = ui -> api_3 -> text();
    QString port = ui -> api_2 -> text();

    quint16 int_port = port.toUShort();

    QHostAddress hostAddress(api);
    if (!(hostAddress.isNull() || hostAddress.protocol() == QAbstractSocket::UnknownNetworkLayerProtocol) && int_port >= 1 && int_port <= 65535) {
        Core core(api,int_port);
    }else {
        QString message = "<html><style>p {color: white;}</style><p>Неверный API или порт</p></body></html>";
        QMessageBox msgBox;
        msgBox.warning(this, "Error", message);
    }
}

