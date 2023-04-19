#include "homewindow.h"
#include "ui_homewindow.h"
#include "profilewindow.h"

HomeWindow::HomeWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HomeWindow)
{
    ui->setupUi(this);
    connect(ui->btnProfile, SIGNAL(clicked()), this, SLOT(ProfilBtnClicked()));
}

void HomeWindow::ProfilBtnClicked()
{
    this->hide();
    ProfileWindow profileWindow;
    profileWindow.exec();
}

HomeWindow::~HomeWindow()
{
    delete ui;
}
