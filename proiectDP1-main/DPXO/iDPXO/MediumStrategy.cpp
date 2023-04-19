#include "MediumStrategy.h"

Position MediumStrategy::GetPosition(const Board& board)
{
	m_contor++;
	if (m_contor % 2)
	{
		return board.GetRandomPosition();
	}
	else
	{
		return DifficultMove(board);
	}
}
