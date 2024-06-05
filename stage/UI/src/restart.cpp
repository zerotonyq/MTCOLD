#include "../include/restart.h"
#include "../UI_Module/ui_restart.h"
#include <QMouseEvent>


restart::restart(Core* core,QWidget *parent)
    : core(core)
    , QDialog(parent)
    , ui(new Ui::restart)
{
    ui->setupUi(this);

    ui -> api_3 ->setPlaceholderText("192.168.100.167");
    ui -> api_2 ->setPlaceholderText("5001");
}

restart::~restart()
{
    delete ui;
}

void restart::on_restart_2_clicked()
{
    QString api = ui -> api_3 -> text();
    QString port = ui -> api_2 -> text();

    quint16 int_port = port.toUShort();

    QHostAddress hostAddress(api);
    if (!(hostAddress.isNull() || hostAddress.protocol() == QAbstractSocket::UnknownNetworkLayerProtocol) && int_port >= 1 && int_port <= 65535) {
        core->changeAddress(api, int_port);
    }else {
        QString message = "<html><style>p {color: white;}</style><p>Неверный API или порт</p></body></html>";
        QMessageBox msgBox;
        msgBox.warning(this, "Error", message);
    }
}
