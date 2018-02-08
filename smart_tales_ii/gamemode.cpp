#include "gamemode.hpp"

bool Gamemode::SurpressDraw() const
{
	return false;
}

bool Gamemode::SurpressUpdate() const
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

Gamemode::Gamemode(Fonts & fontsRef, GameManager & managerRef)
	: fonts(fontsRef),
	manager(managerRef)
{
}
