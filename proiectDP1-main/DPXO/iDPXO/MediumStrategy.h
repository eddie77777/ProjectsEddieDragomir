#pragma once
#include "MediumDifficultStrategy.h"

class MediumStrategy : public MediumDifficultStrategy
{
public:
	Position GetPosition(const Board& board) override;

private:
	uint16_t m_contor = 1;
};

