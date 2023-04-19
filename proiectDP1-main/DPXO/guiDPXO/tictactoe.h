#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <QtWidgets>
#include "mainwindow.h"
#include "UIListener.h"

class TicTacToe : public QMainWindow {
    Q_OBJECT

public:
    explicit TicTacToe(QWidget* parent = nullptr);

private slots:
    void startGameWithComputer();
    void startGameWithPlayer();

private:
    QLabel* titleLabel;
    QLabel* chooseDifficultyLabel;
    QPushButton* playWithComputerButton;
    QPushButton* playWithPlayerButton;
    QComboBox* difficultyComboBox;
};
#endif // TICTACTOE_H