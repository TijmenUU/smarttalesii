/*
	animationsheet.hpp

	The Sheet class loads an animation file and stores the associated texture
	and defined animations. These are publicly available read only

	The AnimatedSprite class uses this.
*/

#pragma once
#include <SFML/Graphics/Texture.hpp>
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
		void LoadFromFile(const std::string & animationFile);

		sf::IntRect GetFrame(const Animation & anim, const unsigned int frameNumber) const;

		// returns nullptr if no animation exists with the given name
		const Animation * GetAnimation(const std::string & name) const;
		// returns empty string if it couldn't find a match
		std::string GetAnimationName(const Animation * ptr) const;

		const sf::Texture & GetTexture() const;
	};
}
