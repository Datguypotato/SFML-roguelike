#include "LevelSign.h"

LevelSign::LevelSign(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, std::string signText)
	:	Interactable(texture, size, position),
		text(new sf::Text())
{
	sf::Font* font = new sf::Font();
	font->loadFromFile("Fonts/04B_30.TTF");
	text->setFont(*font);
	text->setString(signText);
	text->setPosition(body.getPosition() + sf::Vector2f(0, -50)); // offset to make text appear above the sign
	text->setOutlineColor(sf::Color::Black);
	text->setOutlineThickness(3.5f);
	text->setCharacterSize(20);
}

void LevelSign::Draw(sf::RenderWindow& window)
{
	Ground::Draw(window);

	if(InTrigger)
		window.draw(*text);
}
