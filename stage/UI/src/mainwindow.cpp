#include "../include/mainwindow.h"
#include "../UI_Module/ui_mainwindow.h"
#include <QMessageBox>
#include <QPropertyAnimation>
#include <QEvent>
// #include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), core(new Core)
{
    ui->setupUi(this);


    ui ->api ->setPlaceholderText("Введите IP-адрес");
    ui ->port ->setPlaceholderText("Введите порт");
    // if(flag == 1){
    // //     flag = 3939;
    // connect(core, &Core::getIndicatorsQuantityPacket, this, [=](const sIndicatorsCountPack& indicatorsCountPack) {
    //     indicator->setModal(true);
    //     indicator->currentIndicatorsQuantity = indicatorsCountPack.indicatorsCount;
    //     QWidget::close();
    //     indicator->show();
    // });
    // }

}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_request_clicked() {
    api = ui -> api -> text();
    port = ui -> port -> text();
    quint16 int_port = port.toUShort();

    QHostAddress hostAddress(api);
    if (hostAddress.setAddress(api) && int_port >= 1 && int_port <= 65535) {
        core->changeAddress(api,int_port);
        //core->getIndicatorsQuantity();
        indicator = new class indicator(core);
        indicator->setModal(true);
        indicator->currentIndicatorsQuantity = 1;
        QWidget::close();
        indicator->exec();

    }else {
        QString message = "<html><style>p {color: white;}</style><p>Неверный API или порт</p></body></html>";
        QMessageBox msgBox;
        msgBox.warning(this, "Error", message);
    }
}
