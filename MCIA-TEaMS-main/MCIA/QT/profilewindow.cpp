#include "profilewindow.h"
#include "ui_profilewindow.h"

ProfileWindow::ProfileWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProfileWindow)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() | Qt::CustomizeWindowHint |
        Qt::WindowMinimizeButtonHint |
        Qt::WindowMaximizeButtonHint |
        Qt::WindowCloseButtonHint);
}

ProfileWindow::~ProfileWindow()
{
    delete ui;
}
