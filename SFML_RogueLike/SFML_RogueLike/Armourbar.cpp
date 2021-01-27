#include "Armourbar.h"

Armourbar::Armourbar(sf::Vector2f size, sf::Vector2f pos, int playerHealth)
	: Healthbar(size, pos, playerHealth)
{
	sf::Texture* healthbarFillTex = new sf::Texture();
	healthbarFillTex->loadFromFile("Art/UI/ArmourBarFill.png");
	fill.setTexture(healthbarFillTex);
}

void Armourbar::Update(sf::RectangleShape player, float value)
{
	Healthbar::Update(player, value);
	Update(player.getPosition(), value);
}

void Armourbar::Update(sf::Vector2f player, float value)
{
	fill.setPosition(player - position);
}

void Armourbar::Draw(sf::RenderWindow& window)
{
	window.draw(fill);
}
