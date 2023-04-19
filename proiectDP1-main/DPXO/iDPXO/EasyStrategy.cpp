#include "EasyStrategy.h"

Position EasyStrategy::GetPosition(const Board& board)
{
	return board.GetRandomPosition();
}
