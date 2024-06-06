#include "../include/errorwindow.h"
#include "../UI_Module/ui_errorwindow.h"
#include <QTextEdit>

errorWindow::errorWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::errorWindow)
{
    ui->setupUi(this);
    layout = new QVBoxLayout(this);
    textEdit = new QTextEdit(this);

    textEdit->setAcceptRichText(true);
    textEdit->setStyleSheet("QTextEdit { "
                            "color: white; "
                            "background: transparent; "
                            "font-size: 14px; "
                            "border: none; "
                            "padding: 10px; "
                            "font-family: 'Trebuchet MS', sans-serif; "
                            "text-shadow: 1px 1px 2px black; "
                            "}");
    layout->addWidget(textEdit);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);
    textEdit->setMinimumSize(600, 400);
    textEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

errorWindow::~errorWindow()
{
    delete ui;
}

void errorWindow::addErrorOfExceeded(quint32 ma, quint32 indicator) {
    QString message = QString("<p style='color: #8A0000; font-weight: bold;'>Error:</p>"
                              "<p style='margin-left: 20px;'>MA exceeded 1 for indicator <strong>#%1</strong>, current value: <strong>%2</strong></p>")
                          .arg(indicator)
                          .arg(ma);
    textEdit->append(message);
}

void errorWindow::addErrorOfOff(quint32 ma, quint32 indicator) {
    QString message = QString("<p style='color: #8A0000; font-weight: bold;'>Error:</p>"
                              "<p style='margin-left: 20px;'>MA is greater than zero when the indicator <strong>#%1</strong> is off, current value: <strong>%2</strong></p>")
                          .arg(indicator)
                          .arg(ma);
    textEdit->append(message);
}
