#include "MediumDifficultStrategy.h"

Position MediumDifficultStrategy::WinOrBlock(ECellState cellState, const Board& board)
{
	//checks for every row if the last two positions are the same
	for (uint16_t i = 0; i < 3; i++)
	{
		if (board.GetMatrix()[i][1] == board.GetMatrix()[i][2] && board.GetMatrix()[i][1] == cellState && board.GetMatrix()[i][0] == ECellState::Empty)
			return { i, 0 };
	}

	//checks for every column if the last two positions are the same
	for (uint16_t j = 0; j < 3; j++)
	{
		if (board.GetMatrix()[1][j] == board.GetMatrix()[2][j] && board.GetMatrix()[1][j] == cellState && board.GetMatrix()[0][j] == ECellState::Empty)
			return { 0, j };
	}

	//checks for every row if the first and the last positions are the same
	for (uint16_t i = 0; i < 3; i++)
	{
		if (board.GetMatrix()[i][0] == board.GetMatrix()[i][2] && board.GetMatrix()[i][0] == cellState && board.GetMatrix()[i][1] == ECellState::Empty)
			return { i, 1 };
	}

	//checks for every column if the first and the last positions are the same
	for (uint16_t j = 0; j < 3; j++)
	{
		if (board.GetMatrix()[0][j] == board.GetMatrix()[2][j] && board.GetMatrix()[0][j] == cellState && board.GetMatrix()[1][j] == ECellState::Empty)
			return { 1, j };
	}

	//checks for every row if the first and the second positions are the same
	for (uint16_t i = 0; i < 3; i++)
	{
		if (board.GetMatrix()[i][0] == board.GetMatrix()[i][1] && board.GetMatrix()[i][1] == cellState && board.GetMatrix()[i][2] == ECellState::Empty)
			return { i, 2 };
	}

	//checks for every column if the first and the second positions are the same
	for (uint16_t j = 0; j < 3; j++)
	{
		if (board.GetMatrix()[0][j] == board.GetMatrix()[1][j] && board.GetMatrix()[0][j] == cellState && board.GetMatrix()[2][j] == ECellState::Empty)
			return { 2, j };
	}

	//checks for first diagonal
	if (board.GetMatrix()[0][0] == board.GetMatrix()[1][1] && board.GetMatrix()[0][0] == cellState && board.GetMatrix()[2][2] == ECellState::Empty)
		return { 2, 2 };

	if (board.GetMatrix()[0][0] == board.GetMatrix()[2][2] && board.GetMatrix()[0][0] == cellState && board.GetMatrix()[1][1] == ECellState::Empty)
		return { 1, 1 };

	if (board.GetMatrix()[2][2] == board.GetMatrix()[1][1] && board.GetMatrix()[1][1] == cellState && board.GetMatrix()[0][0] == ECellState::Empty)
		return { 0, 0 };


	//checks for second diagonal
	if (board.GetMatrix()[0][2] == board.GetMatrix()[1][1] && board.GetMatrix()[1][1] == cellState && board.GetMatrix()[2][0] == ECellState::Empty)
		return { 2, 0 };
	if (board.GetMatrix()[0][2] == board.GetMatrix()[2][0] && board.GetMatrix()[0][2] == cellState && board.GetMatrix()[1][1] == ECellState::Empty)
		return { 1, 1 };
	if (board.GetMatrix()[1][1] == board.GetMatrix()[2][0] && board.GetMatrix()[1][1] == cellState && board.GetMatrix()[0][2] == ECellState::Empty)
		return { 0, 2 };

	return { -1, -1 };
}

Position MediumDifficultStrategy::Corner(ECellState cellState, const Board& board)
{
	if (board.GetMatrix()[0][0] == board.GetMatrix()[2][2] && board.GetMatrix()[0][0] != cellState && board.GetMatrix()[0][1] == ECellState::Empty)
		return { 0, 1 };
	if (board.GetMatrix()[0][2] == board.GetMatrix()[2][0] && board.GetMatrix()[0][2] != cellState && board.GetMatrix()[0][1] == ECellState::Empty)
		return { 0, 1 };
	if (board.GetMatrix()[0][0] == ECellState::Empty)
		return { 0, 0 };
	if (board.GetMatrix()[0][2] == ECellState::Empty)
		return { 0, 2 };
	if (board.GetMatrix()[2][0] == ECellState::Empty)
		return { 2, 0 };
	if (board.GetMatrix()[2][2] == ECellState::Empty)
		return { 2, 2 };

	return { -1, -1 };

}

Position MediumDifficultStrategy::DifficultMove(const Board& board)
{
	if (board.GetMatrix()[1][1] == ECellState::Empty)
		return { 1, 1 };

	Position pos;
	pos = WinOrBlock(ECellState::Zero, board);
	if (pos.first != -1 && pos.second != -1)
		return pos;
	pos = WinOrBlock(ECellState::Cross, board);
	if (pos.first != -1 && pos.second != -1)
		return pos;
	pos = Corner(ECellState::Zero, board);
	if (pos.first != -1 && pos.second != -1)
		return pos;
	pos = MiddleEdge(board);
	if (pos.first != -1 && pos.second != -1)
		return pos;

	return { -2, -2 };
}

Position MediumDifficultStrategy::MiddleEdge(const Board& board)
{
	if (board.GetMatrix()[0][1] == ECellState::Empty)
		return { 0, 1 };
	if (board.GetMatrix()[1][2] == ECellState::Empty)
		return { 1, 2 };
	if (board.GetMatrix()[2][1] == ECellState::Empty)
		return { 2, 1 };
	if (board.GetMatrix()[1][0] == ECellState::Empty)
		return { 1, 0 };

	return { -1, -1 };
}
