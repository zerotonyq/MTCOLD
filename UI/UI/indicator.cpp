#include "indicator.h"
#include "error.h"
#include "errorwindow.h"
#include "qbuttongroup.h"
#include "restart.h"
#include "ui_indicator.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QEvent>

#include <QButtonGroup>

QDialog* dialog = nullptr; // Глобальная переменная для хранения указателя на диалог

indicator::indicator(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::indicator)
{
    ui->setupUi(this);

    ui->labelInfo0->hide();
    ui->labelInfo1->hide();

    installEventFilter(this);

    // Создаем объект группы кнопок
    QButtonGroup *buttonGroup = new QButtonGroup(this);

    // Пример связывания кнопок с группой
    buttonGroup->addButton(ui->info0, 0); // Уникальный идентификатор 0
    buttonGroup->addButton(ui->info1, 1); // Уникальный идентификатор 1
    buttonGroup->addButton(ui->info2, 2); // Уникальный идентификатор 2
    buttonGroup->addButton(ui->info3, 3); // Уникальный идентификатор 3
    buttonGroup->addButton(ui->info4, 4); // Уникальный идентификатор 4
    buttonGroup->addButton(ui->restart, 5); // перезапуск

    // Количество индикаторов

    quint32 sii = static_cast<quint32>(count);
    _itoa_s(sii,scount,10);
    ui->indiccount->setText(scount);

    connect(buttonGroup, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(onButtonClicked(QAbstractButton*)));
}

indicator::~indicator()
{
    delete ui;
}

// void indicator::on_build_clicked()
// {
//     // Проверяем, открыто ли уже окно restart
//     if (restartWindow != nullptr && restartWindow->isVisible())
//     {
//         restartWindow->close();
//         return;
//     }

//     // Создаем новый экземпляр окна restart
//     restartWindow = new restart(this);
//     restartWindow->setWindowFlags(Qt::CustomizeWindowHint);
//     QPoint mainWinPos = this->pos();
//     int offsetX = 0;
//     int offsetY = 0;
//     restartWindow->move(mainWinPos + QPoint(offsetX, offsetY));

//     // Открываем новое окно в модальном режиме
//     // restartWindow->exec();
//     restartWindow->show();
// }

void indicator::on_build_clicked()
{
    if (restartWindow != nullptr && restartWindow->isVisible())
    {
        restartWindow->close();
        return;
    }

    // Создаем новый экземпляр окна restart
    restartWindow = new restart(this);
    restartWindow->setWindowFlags(Qt::CustomizeWindowHint);

    // Получаем позицию кнопки, на которую нажимают
    int offsetX = 30;
    int offsetY = 40;
    restartWindow->move(QPoint(offsetX, offsetY));

    // Открываем новое окно в модальном режиме
    // restartWindow->exec();
    restartWindow->show();
}


void indicator::on_mistakes_clicked()
{
    // Проверяем, открыто ли уже окно errorWindow
    if (errorwindow != nullptr && errorwindow->isVisible())
    {
        errorwindow->close();
        return;
    }

    // Создаем новый экземпляр окна errorWindow
    errorwindow = new errorWindow(this);
    errorwindow->setWindowFlags(Qt::CustomizeWindowHint);

    int offsetX = 400;
    int offsetY = 40;
    errorwindow->move(QPoint(offsetX, offsetY));

    // Открываем новое окно в модальном режиме
    // errorwindow->exec();
    errorwindow->show();
}

void indicator::onButtonClicked(QAbstractButton* button)
{
    if (button == ui->info0)
    {

        QString htmlText = R"(
            <!DOCTYPE html>
            <html lang="ru">
            <head>
            <meta charset="UTF-8">
            <title>Информация об индикаторе</title>
            <style>
                body {
                    font-family: Arial, sans-serif;
                    display: flex;
                    justify-content: center;
                    align-items: center;
                    height: 100vh;
                }
                .container {
                    max-width: 600px;
                    padding: 20px;
                    border-radius: 8px;
                    box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
                    text-align: center;
                    line-height: 2;
                    border: 5px solid #ccc;
                    background-color: rgb(194, 194, 194);
                    background-image: url(:/image/resources/img/white_back.jpg);
                }
                .header {
                    font-size: 30px;
                    font-weight: bold;
                    margin-bottom: 15px;
                }
                .serial-number,
                .color,
                .current-level {
                    margin-bottom: 20px;
                }
                .serial-number-title,
                .color-title,
                .current-level-title {
                    font-weight: bold;
                    font-size: 22px;
                    font-family: 'Random Grotesque Standard Bold', sans-serif;
                }
                .color-value {
                    color: #8a0000;
                    font-size: 28px;
                }
                .current-level-value {
                    font-size: 40px;
                    color: #8a0000;
                }
                .serial-number div,
                .color div {
                    font-size: 24px;
                }
            </style>
            </head>
            <body>
                <div class="container">
                    <div class="header">Информация об индикаторе №0</div>
                    <div class="serial-number">
                        <div class="serial-number-title">серийный номер:</div>
                        <div>tjfxkd-fkencd-kj:sw2</div>
                    </div>
                    <div class="color">
                        <div class="color-title">цвет:</div>
                        <div class="color-value">красный</div>
                        <div><b>Тип:</b></div>
                        <div>индикатор</div>
                    </div>
                    <div class="current-level">
                        <div class="current-level-title">Уровень тока на данный момент</div>
                        <div class="current-level-value">2.328 А</div>
                    </div>
                </div>
            </body>
            </html>
            )";


        ui->label->setText(htmlText);

        ui->label->setText(htmlText);
        ui->label->setStyleSheet(R"(
        QLabel {
            border: 5px solid rgb(221, 221, 221);
            background-color: rgb(194, 194, 194);
            background-image: url(':/image/resources/img/white_back.jpg');
            border-radius: 35px;
            display: flex;
            width: 520px;
            height: 590px;

        }
        .header {
            font-size: 30px;
            font-weight: bold;
            margin-bottom: 15px;
        }
        .serial-number-title, .color-title, .current-level-title {
            font-weight: bold;
            font-size: 22px;
            font-family: 'Random Grotesque Standard Bold', sans-serif;
        }
        .color-value {
            color: #8a0000;
            font-size: 28px;
        }
        .current-level-value {
            font-size: 40px;
            color: #8a0000;
        }
        .serial-number div, .color div {
            font-size: 24px;
        }
        )");

        // Прячем кнопку после нажатия
        ui->info0->hide();

    }
    else if (button == ui->info1)
    {
        // ui->labelInfo1->show();
        // ui->label_4->hide();
        // ui->label->hide();

        //ui->info1->hide();
        ui->info0->show();
        ui->info3->show();
        ui->info2->show();
        ui->info4->show();
        ui -> label -> setText("1");

        ui->info1->hide();
    }
    else if (button == ui->info2)
    {
        // ui->labelInfo1->show();
        // ui->label_4->hide();
        // ui->label->hide();

        // ui->info1->hide();
        ui->info0->show();
        ui->info1->show();
        ui->info4->show();
        ui->info3->show();
        ui -> label -> setText("2");

        ui->info2->hide();
    }
    else if (button == ui->info3)
    {
        ui -> label -> setText("3");
        ui->info0->show();
        ui->info1->show();
        ui->info2->show();
        ui->info4->show();
        ui->info3->hide();
    }
    else if (button == ui->info4)
    {
        ui->info0->show();
        ui->info1->show();
        ui->info2->show();
        ui->info3->show();
        ui -> label -> setText("4");

        ui->info4->hide();
    }
    else if (button == ui->restart)
    {
        ui->info0->show();
        ui->info1->show();
        ui->info2->show();
        ui->info3->show();
        ui->info4->show();
        ui -> label -> setText("перезапуск индикаторов");
    }


}

// bool indicator::eventFilter(QObject *obj, QEvent *event)
// {
//     if (event->type() == QEvent::MouseButtonPress)
//     {
//         // Проверяем, если окно restart открыто, то закрываем его
//         if (dialog != nullptr && dialog->isVisible())
//             dialog->close();
//     }

//     return false;
// }





// void indicator::on_toggle0_toggled(bool checked)
// {
//     if (checked){
//         core.turnOnIndicator();
//     }
// }

