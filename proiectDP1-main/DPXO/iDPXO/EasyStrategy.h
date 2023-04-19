#include "IStrategy.h"

class EasyStrategy : public IStrategy
{
public:
	Position GetPosition(const Board& board) override;
};