#include "../include/mainwindow.h"
#include "../UI_Module/ui_mainwindow.h"
#include <QMessageBox>
#include <QPropertyAnimation>
#include <QEvent>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // this->setWindowFlags(Qt::CustomizeWindowHint); отсутсвие рамки


    ui ->api ->setPlaceholderText("Введите IP-адрес");
    ui ->port ->setPlaceholderText("Введите порт");
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_request_clicked() {
    QString api = ui -> api -> text();
    QString port = ui -> port -> text();

    quint16 int_port = port.toUShort();

    indicator indicator;

    //Core core(api,int_port);
    //restart.setCore(&core);
    QWidget::close();
    indicator.setModal(true);
    indicator.exec();



    // QHostAddress hostAddress(api);
    // if (!(hostAddress.isNull() || hostAddress.protocol() == QAbstractSocket::UnknownNetworkLayerProtocol) && int_port >= 1 && int_port <= 65535) {
    //     core = new Core(api,int_port);
    //     restart* Restart = new restart();
    //     Restart->setCore(core);
    //     QWidget::close();
    //     indicator.setModal(true);
    //     indicator.exec();
    // }
    // else {
    //     QString message = "<html><style>p {color: white;}</style><p>Неверный API или порт</p></body></html>";
    //     QMessageBox msgBox;
    //     msgBox.warning(this, "Error", message);
    //     // QString message = "<html><p style=;color:red;"">Неверный API или порт</p></html>";

    //     // QLabel *label = new QLabel(message);
    //     // label->setAlignment(Qt::AlignCenter);
    //     // label->setStyleSheet("QLabel { color : red; }");
}
