#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include <unordered_map>

namespace Animation
{
	// Helper struct
	struct Animation
	{
		sf::Vector2u frameStart;	// offset in pixels
		sf::Vector2u frameSize;		// in pixels
		unsigned int frameMargin;	// in pixels
		unsigned int frameCount;
		unsigned int frameTime;		// in milliseconds
		bool reverse;
		bool loop;

		Animation();
	};

	class Sheet
	{
	private:
		sf::Texture texture;
		std::unordered_map<std::string, Animation> animations;
	
	public:
		virtual void LoadFromFile(const std::string & animationFile);

		virtual sf::IntRect GetFrame(const Animation & anim, const unsigned int frameNumber) const;

		// returns nullptr if no animation exists with the given name
		virtual const Animation * GetAnimation(const std::string & name) const;
		// returns empty string if it couldn't find a match
		virtual std::string GetAnimationName(const Animation * ptr) const;

		const sf::Texture & GetTexture() const;
	};
}
