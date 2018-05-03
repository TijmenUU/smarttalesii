#include "gameovermessage.hpp"

#include "resourcecache.hpp"

#include <array>
#include <string>

static std::string GetCatchphrase()
{
	const static std::array<std::string, 5> messages = {
		"Small accidents are scary!", 
		"Ouch!",
		"Practice makes perfect!",
		"Tech up!",
		"Big brother is watching?"
	};
	static unsigned int idx = 0U;
	
	if(idx >= messages.size())
		idx = 0U;
	
	return messages[idx++];
}

static std::string GetInformationStr()
{
	const static std::array<std::string, 5> messages = {
		"In 2016, 96 000 Dutch elderly had to visit the\nemergency after an accident at home.", // Cijferrapportage Valongevallen 65 jaar en ouder, 2016
		"That same year tripping over accounted for 23%\nof the total causes.", // Cijferrapportage Valongevallen 65 jaar en ouder, 2016
		"Nobody likes sitting still at home all day,\nnot even the elderly.", // AAL Forum 2016: elderly want to have an active part in society
		"A lot of elderly are actually a bit scared of IT,\nwhilst it could help them a lot.", // The elderly are afraid of using IT systems, KLEINBERGER et al 2007
		"Not really, simple but helpful aids like automatic\nlights only look at temperature differences." // Privacy, Identity and Security in Ambient Intelligence, Friedewald et al 2005
	};
	static unsigned int idx = 0U;

	if(idx >= messages.size())
		idx = 0U;

	return messages[idx++];
}

void GameoverMessage::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(catchPhrase, states);
	target.draw(information, states);
}

GameoverMessage::GameoverMessage(const float centerX, const float y)
	: catchPhrase(GetCatchphrase(), ResourceCache::GetInstance().GetFont("commodore"), 42),
	information(GetInformationStr(), ResourceCache::GetInstance().GetFont("commodore"), 22)
{
	auto bounds = catchPhrase.getGlobalBounds();
	catchPhrase.setFillColor(sf::Color::White);
	catchPhrase.setPosition(bounds.left + (centerX - (bounds.width / 2.f)), y);

	bounds = information.getGlobalBounds();
	information.setFillColor(sf::Color::White);
	information.setPosition(bounds.left + (centerX - (bounds.width / 2.f)), y + 55.f);
}
