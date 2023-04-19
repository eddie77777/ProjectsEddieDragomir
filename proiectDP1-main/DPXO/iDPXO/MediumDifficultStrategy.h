#pragma once
#include "IStrategy.h"

class MediumDifficultStrategy : public IStrategy 
{
private:
	Position WinOrBlock(ECellState cellState, const Board& board);
	Position MiddleEdge(const Board& board);
	Position Corner(ECellState cellState, const Board& board);
	
protected:
	Position DifficultMove(const Board& board);
};

