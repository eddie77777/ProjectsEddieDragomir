#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QResizeEvent>
#include "Game.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(EGameMode gameMode, EStrategyType strategyType, QWidget* parent = nullptr);
    void HandleButton();
    ~MainWindow();
    IGamePtr GetGame();
    void SetListener(std::shared_ptr<IGameListener> listener);
    char ECellStateToChar(ECellState cellState);
private:
    QPushButton* buttons[3][3];
    std::shared_ptr<IGameListener> m_listener;
    IGamePtr m_game;
    EGameMode m_gameMode;
    EStrategyType m_strategy;

    void UpdateGUI();
};

#endif // MAINWINDOW_H