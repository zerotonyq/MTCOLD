#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include "indicator.h"


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

    indicator indicator;

    if(api == "192.168.100.167" && port == "5001") {
        QWidget::close();
        indicator.setModal(true);
        indicator.exec();
    }
    else {
        QString message = "<html><style>p {color: white;}</style><p>Неверный API или порт</p></body></html>";
        QMessageBox msgBox;
        msgBox.warning(this, "Error", message);
        // QString message = "<html><p style=;color:red;"">Неверный API или порт</p></html>";

        // QLabel *label = new QLabel(message);
        // label->setAlignment(Qt::AlignCenter);
        // label->setStyleSheet("QLabel { color : red; }");

        // QVBoxLayout *layout = new QVBoxLayout;
        // layout->addWidget(label);
        // layout->addStretch(); // добавляем растягивающий элемент

        // // Добавляем вашу логику для размещения виджета под кнопкой в основном окне
        // // Например, если у вас есть главное окно mainWindow, то можете добавить label к нему так:
        // isWindow()->layout()->addLayout(layout);

        // ui -> label_2 -> setText("АУЕ");

    }
}

