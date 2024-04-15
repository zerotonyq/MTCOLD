#include "../include/mainwindow.h"
#include <QFile>
#include <QFont>
#include <QFontDatabase>
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


    int boldFontId = QFontDatabase::addApplicationFont(":/fonts/RG-StandardBold.ttf");
    if (boldFontId == -1) {
        qDebug() << "Failed to load RG-StandardBold font!";
    } else {
        QString boldFamily = QFontDatabase::applicationFontFamilies(boldFontId).at(0);
        // Можете установить этот шрифт как шрифт приложения, если хотите
        // QFont boldFont(boldFamily);
        // QApplication::setFont(boldFont);
    }

    int bookFontId = QFontDatabase::addApplicationFont(":/fonts/RG-StandardBook.ttf");
    if (bookFontId == -1) {
        qDebug() << "Failed to load RG-StandardBook font!";
    } else {
        QString bookFamily = QFontDatabase::applicationFontFamilies(bookFontId).at(0);
        // Можете установить этот шрифт как шрифт приложения, если хотите
        // QFont bookFont(bookFamily);
        // QApplication::setFont(bookFont);
    }


    return a.exec();
}
