#pragma once
#include "IPlayer.h"

class CPlayer : public IPlayer
{
public:
	CPlayer() = default;
private:
	char m_symbol;
};

