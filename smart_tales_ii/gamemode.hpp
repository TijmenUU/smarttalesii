#pragma once
#include "inputhandler.hpp"
#include "resourcecache.hpp"

#include <memory>
#include <SFML/Graphics.hpp>

const float cWorldWidth = 1280.f; // in pixels
const float cWorldHeight = 720.f; // in pixels

class GameManager;

class Gamemode : public sf::Drawable
{
private:
protected:
	friend class GameManager;

	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const = 0;

	virtual bool SurpressDraw() const;
	virtual bool SurpressUpdate() const;
	virtual void OnExit();
	virtual void OnEnter();

	virtual void Setup() = 0;
	virtual void Update(const sf::Time & elapsed, const Inputhandler & input) = 0;

public:
	Gamemode() = default;
	virtual ~Gamemode() = default;
};