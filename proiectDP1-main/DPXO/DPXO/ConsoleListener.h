#pragma once
#include "IGame.h"


class ConsoleListener : public IGameListener
{
public:
	ConsoleListener(int no, IGamePtr game);
	void OnMakeMove(Position pos, int currentPlayer) override;
	void OnGameOver(int currentPlayer, EGameState gameState) override;

	void ShowTable(std::ostream& os, uint16_t currentPlayer);
	char ECellStateToChar(ECellState cellState);

private:
	int m_no;
	IGamePtr m_game;
};

