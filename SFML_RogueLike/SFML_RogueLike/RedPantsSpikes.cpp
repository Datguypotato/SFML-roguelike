#include "RedPantsSpikes.h"

RedPantsSpikes::RedPantsSpikes(sf::Texture* itemText, std::string name)
	:	RedPants(itemText, name)
{
	stunPercentage = 40;
	stunTime = 2;
}
