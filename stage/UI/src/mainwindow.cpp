#include "../include/mainwindow.h"
#include "../UI_Module/ui_mainwindow.h"
#include <QMessageBox>
#include <QPropertyAnimation>
#include <QEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), core(new Core)
{
    ui->setupUi(this);


    ui ->api ->setPlaceholderText("Введите IP-адрес");
    ui ->port ->setPlaceholderText("Введите порт");
    // connect(core, &Core::getIndicatorsQuantityPacket, this, [=](const sIndicatorsCountPack& indicatorsCountPack) {
    //     QHostAddress hostAddress(api);
    //     if (!(hostAddress.isNull() || hostAddress.protocol() == QAbstractSocket::UnknownNetworkLayerProtocol) && port.toUShort() >= 1 && port.toUShort() <= 65535) {
    //         core = new Core(api,port.toUShort());
    //         indicator indicator(core);
    //         indicator.currentIndicatorsQuantity = indicatorsCountPack.indicatorsCount;
    //         QWidget::close();
    //         indicator.setModal(true);
    //         indicator.exec();
    //     }
    //     else {
    //         QString message = "<html><style>p {color: white;}</style><p>Неверный API или порт</p></body></html>";
    //         QMessageBox msgBox;
    //         msgBox.warning(this, "Error", message);
    //     }
    // });

}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_request_clicked() {
    api = ui -> api -> text();
    port = ui -> port -> text();

    //core->getIndicatorsQuantity();
    QWidget::close();
    indicator indicator(core);
    indicator.setModal(true);
    indicator.currentIndicatorsQuantity = 4;
    indicator.exec();
}
