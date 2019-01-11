#include "gamemode.hpp"

bool Gamemode::SuppressDraw() const
{
	return false;
}

bool Gamemode::SuppressUpdate() const
{
	return false;
}

void Gamemode::OnExit()
{
	return;
}

void Gamemode::OnEnter()
{
	return;
}
