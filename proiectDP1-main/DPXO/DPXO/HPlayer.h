#pragma once
#include "IPlayer.h"

class HPlayer : public IPlayer
{
public:
	HPlayer() = default;
private:
	char m_symbol;
};

