#include "../include/mainwindow.h"
#include <QFile>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //css
    QFile file("qrc:/style/style.css");
    file.open(QFile::ReadOnly);
    a.setStyleSheet(file.readAll());
    MainWindow w;
    w.show();

    return a.exec();
}
