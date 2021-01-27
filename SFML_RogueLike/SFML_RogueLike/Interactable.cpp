#include "Interactable.h"

Interactable::Interactable(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, std::string signText)
	:	Ground(texture, size, position),
		InTrigger(false),
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

Interactable::~Interactable()
{
}

void Interactable::CheckTrigger(Collider pColl)
{
	InTrigger = GetCollider().CheckTrigger(pColl);
}

void Interactable::Draw(sf::RenderWindow& window)
{
	Ground::Draw(window);
	if (InTrigger)
		window.draw(*text);
}

