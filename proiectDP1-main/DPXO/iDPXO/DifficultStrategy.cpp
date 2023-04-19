#include "DifficultStrategy.h"

Position DifficultStrategy::GetPosition(const Board& board)
{
	return DifficultMove(board);
}
