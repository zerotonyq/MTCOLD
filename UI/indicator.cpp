#include "indicator.h"
#include "error.h"
#include "errorwindow.h"
#include "restart.h"
#include "ui_indicator.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QEvent>

QDialog* dialog = nullptr; // Глобальная переменная для хранения указателя на диалог

indicator::indicator(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::indicator)
{
    ui->setupUi(this);

    ui->labelInfo0->hide();
    ui->labelInfo1->hide();

}

indicator::~indicator()
{
    delete ui;
}

void indicator::on_build_clicked()
{
    restart *restartWindow = new restart(); // Создание объекта нового окна

    // Установка позиции нового окна относительно основного окна
    QPoint mainWinPos = this->pos(); // Получение позиции основного окна
    int offsetX = 30; // Горизонтальное смещение (x)
    int offsetY = 70; // Вертикальное смещение (y)
    restartWindow->move(mainWinPos + QPoint(offsetX, offsetY)); // Установка позиции нового окна

    restartWindow->exec(); // Открытие нового окна в модальном режиме
}

void indicator::on_mistakes_clicked()
{
    // QMessageBox::warning(this, "ошибки", "<html><style>p {color: white;}</style><p>Внимание! В индикаторе №1 уровень тока превышает 1 А</p></html>");
    errorWindow *errorwindow = new errorWindow(); // Создание объекта нового окна

    // Установка позиции нового окна относительно основного окна
    QPoint mainWinPos = this->pos(); // Получение позиции основного окна
    int offsetX = 620; // Горизонтальное смещение (x)
    int offsetY = 70; // Вертикальное смещение (y)
    errorwindow->move(mainWinPos + QPoint(offsetX, offsetY)); // Установка позиции нового окна

    errorwindow->exec(); // Открытие нового окна в модальном режиме

}


void indicator::on_info0_clicked()
{
    // Изменяем текст в QLabel на информацию об индикаторе
    ui->labelInfo0->show();
    ui->label->hide();
    ui->label_4->hide();

    // Прячем кнопку после нажатия
    ui->info0->hide();
}


void indicator::on_info0_2_clicked()
{
    ui->labelInfo1->show();
    ui->label_4->hide();
    ui->label->hide();

    // Прячем кнопку после нажатия
    ui->info0_2->hide();
}

