#ifndef PROFILEWINDOW_H
#define PROFILEWINDOW_H

#include <QDialog>

namespace Ui {
class ProfileWindow;
}

class ProfileWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ProfileWindow(QWidget *parent = nullptr);
    ~ProfileWindow();

private:
    Ui::ProfileWindow *ui;
};

#endif // PROFILEWINDOW_H
