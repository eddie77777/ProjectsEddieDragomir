#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lblUsernameError->setWordWrap(true);
    ui->lblPasswordError->setWordWrap(true);
    loadStylesheet();
    linkSlots();
}


void MainWindow::loadStylesheet()
{
    QFile stylesFile("../../../QT/stylesheet.qss");
    if (!stylesFile.exists())
        qInfo() << "Stylesheet doesnt exist";
    stylesFile.open(QFile::ReadOnly);
    if (!stylesFile.isOpen())
        qInfo() << "Stylesheet could not be opened";
    QString StyleSheet = QLatin1String(stylesFile.readAll());
    qApp->setStyleSheet(StyleSheet);

}

void MainWindow::linkSlots()
{
    connect(ui->btnLogin, SIGNAL(clicked()), this, SLOT(LoginBtnClicked()));
    connect(ui->btnRegister, SIGNAL(clicked()), this, SLOT(RegisterBtnClicked()));
    connect(ui->lneUsername, SIGNAL(textEdited(QString)), this, SLOT(LNETextEdited(QString)));
    connect(ui->lnePassword, SIGNAL(textEdited(QString)), this, SLOT(LNETextEdited(QString)));
}

void MainWindow::LoginBtnClicked()
{
    std::string username = ui->lneUsername->text().toStdString();
    std::string password = ui->lnePassword->text().toStdString();
    AuthService authService;
    try {
        authService.LoginUser(*(new User(username, password)));
        this->hide();
        HomeWindow homeWindow;
        homeWindow.setModal(true);
        homeWindow.exec();
    }
    catch (CodedException e) {
        /* AuthService throws error if user is not found.*/
        ui->lblUsernameError->setText("Username or password invalid.");
    }
}


void MainWindow::RegisterBtnClicked()
{
    OperationStatusToMessage ostm;
    DBValidation validator;
    AuthService authService;
    qInfo() << " Register user:";
    std::string username = ui->lneUsername->text().toStdString();
    std::string password = ui->lnePassword->text().toStdString();
    try {
        authService.RegisterUser(*(new User(username, password)));
        HomeWindow homeWindow;
        homeWindow.setModal(true);
        homeWindow.exec();
    }
    catch (CodedException e) {
        auto fieldMessage = e.GetMessage();
        if (fieldMessage == "username") {
            ui->lblUsernameError->setText(QString::fromStdString(
                validator.UsernameErrorMessage(e.GetCode())
            ));
        }
        else {
            ui->lblPasswordError->setText(QString::fromStdString(
                validator.PasswordErrorMessage(e.GetCode())
            ));
        }
    }
}

void MainWindow::LNETextEdited(QString string)
{
    if (qobject_cast<QLineEdit*>(sender()) == ui->lneUsername)
        ui->lblUsernameError->setText("");
    else ui->lblPasswordError->setText("");
}

MainWindow::~MainWindow()
{
    delete ui;
}