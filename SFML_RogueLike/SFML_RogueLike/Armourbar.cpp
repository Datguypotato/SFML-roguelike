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
	fill.setPosition(player.getPosition() - position);
}

void Armourbar::Draw(sf::RenderWindow& window)
{
	window.draw(fill);
}
