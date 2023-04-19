#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <AuthService.h>
#include "homewindow.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void loadStylesheet();
    void linkSlots();

private slots:
    void LoginBtnClicked();
    void RegisterBtnClicked();
    void LNETextEdited(QString string);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
