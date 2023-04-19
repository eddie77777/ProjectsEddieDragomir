#pragma once
#include "IGame.h"
#include <QPushButton>
class MainWindow;
class UIListener : public IGameListener
{
public:
    UIListener(int no, IGamePtr game);
    void ConnectToMainWindow(MainWindow* mainWindow);
    void OnMakeMove(Position pos, int currentPlayer) override;
    void OnGameOver(int currentPlayer, EGameState gameState) override;
    char ECellStateToChar(ECellState cellState);
private:
    int m_no;
    IGamePtr m_game;
    MainWindow* m_mainWindow;
};