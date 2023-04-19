#include "UIListener.h"
#include<QMessagebox>
#include<QtCore/QObject>
#include<QtWidgets>

UIListener::UIListener(int no, IGamePtr game) : m_no(no)
, m_game(game)
{
}

void UIListener::OnMakeMove(Position pos, int currentPlayer)
{
    //QPushButton* button;
    //connect(button, &QPushButton::clicked,this,&UIListener::OnMakeMove);
    //QPushButton* button = qobject_cast<QPushButton*>(sender());
    
}


void UIListener::OnGameOver(int currentPlayer, EGameState gameState)
{
    if (gameState == EGameState::Win) {
        QString message = QString("Player %1 wins!").arg(currentPlayer);
        QMessageBox::information(nullptr, "Game Over", message);
    }
    else
        QMessageBox::information(nullptr, "Game Over", "It's a tie!");
}
char UIListener::ECellStateToChar(ECellState cellState)
{
    if (cellState == ECellState::Zero)
        return '0';
    else if (cellState == ECellState::Cross)
        return 'X';
    return ' ';
}