#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\System\Clock.hpp>
#include <string>
#include <unordered_map>

struct Animation
{
	sf::Vector2u frameStart;	// offset in pixels
	sf::Vector2u frameSize;		// in pixels
	unsigned int frameMargin;	// in pixels
	unsigned int frameCount;
	unsigned int frameTime;		// in milliseconds
	bool reverse;

	Animation();
};

class AnimatedSprite : public sf::Sprite
{
private:
	std::unordered_map<std::string, Animation> animations;
	const Animation * currentAnimation;
	unsigned int currentFrame;
	unsigned int currentFrameTime;

	void GetNextFrame();

public:
	std::vector<std::string> GetAnimations() const;

	// Returns false if animation already exists
	bool AddAnimation(const Animation animation, const std::string & name);
	// May overwrite an exisiting entry
	void ForceAddAnimation(const Animation animation, const std::string & name);
	bool SetAnimation(const std::string & name);
	bool RemoveAnimation(const std::string & name);

	void FlipHorizontally();
	void FlipVertically();
	// May throw a runtime_error if the file or the file definition is wrong
	void Load(const std::string & animationFile, sf::Texture & textureStorage);
	void Update(const sf::Time & elapsed);

	AnimatedSprite();
};
