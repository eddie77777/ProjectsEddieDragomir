#pragma once
#include "MediumDifficultStrategy.h"

class DifficultStrategy : public MediumDifficultStrategy
{
public:
	Position GetPosition(const Board& board) override;
};

