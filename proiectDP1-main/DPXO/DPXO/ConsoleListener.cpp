#include "ConsoleListener.h"
#include <iostream>

ConsoleListener::ConsoleListener(int no, IGamePtr game)
	: m_no(no)
	,m_game(game)
{
}

void ConsoleListener::OnMakeMove(Position pos, int currentPlayer)
{
	system("CLS");
	std::cout << "Last move: ";
	std::cout << "Player: " << currentPlayer << "// Pos: " 
	<< '[' << pos.first + 1 << " , " << pos.second + 1 << ']' << "\n";
	ShowTable(std::cout, 3 - currentPlayer);
}

void ConsoleListener::OnGameOver(int currentPlayer, EGameState gameState)
{
	std::cout << "GAME OVER!!! ";
	if (gameState == EGameState::Win)
		std::cout << "Player: " << currentPlayer << " won the game!\n";
	else
		std::cout << "Tie!\n";
}


void ConsoleListener::ShowTable(std::ostream& os, uint16_t currentPlayer)
{
	os << "Player " << currentPlayer << "'s turn.\n";
	BoardContent bc = m_game->GetBoardContent();
	os << "  |  1" << "  |  2" << "  |  3\n";
	os << "--|-----|-----|-----\n";
	os << "  |     " << '|' << "     " << '|' << "     \n";
	os << "1 |" << "  " << ECellStateToChar(bc[0][0]) << "  " << '|' << "  " << ECellStateToChar(bc[0][1]) << "  " << '|' << "  " << ECellStateToChar(bc[0][2]) << "  \n";
	os << "  |     " << '|' << "     " << '|' << "     \n";
	os << "--|-----" << '|' << "-----" << '|' << "-----\n";
	os << "  |     " << '|' << "     " << '|' << "     \n";
	os << "2 |" << "  " << ECellStateToChar(bc[1][0]) << "  " << '|' << "  " << ECellStateToChar(bc[1][1]) << "  " << '|' << "  " << ECellStateToChar(bc[1][2]) << "  \n";
	os << "  |     " << '|' << "     " << '|' << "     \n";
	os << "--|-----" << '|' << "-----" << '|' << "-----\n";
	os << "  |     " << '|' << "     " << '|' << "     \n";
	os << "3 |" << "  " << ECellStateToChar(bc[2][0]) << "  " << '|' << "  " << ECellStateToChar(bc[2][1]) << "  " << '|' << "  " << ECellStateToChar(bc[2][2]) << "  \n";
	os << "  |     " << '|' << "     " << '|' << "     \n";
}



char ConsoleListener::ECellStateToChar(ECellState cellState)
{
	if (cellState == ECellState::Zero)
		return '0';
	else if (cellState == ECellState::Cross)
		return 'X';
	return ' ';
}
