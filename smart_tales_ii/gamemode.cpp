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

Gamemode::Gamemode(ResourceCache & resourceCacheRef, GameManager & managerRef)
	: resourceCache(resourceCacheRef),
	manager(managerRef)
{
}
