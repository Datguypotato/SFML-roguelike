#include "Healthbar.h"

Healthbar::Healthbar(sf::Vector2f size, sf::Vector2f pos, int playerHealth)
	:	UIComponent(size, pos)
{
	maxHealth = playerHealth;

	sf::Texture* healthbarTex = new sf::Texture();
	healthbarTex->loadFromFile("Art/UI/HealthBar.png");
	box.setTexture(healthbarTex);

	fill = sf::RectangleShape(size);
	fill.setOrigin(fill.getSize() / 2.0f);
	sf::Texture* healthbarFillTex = new sf::Texture();
	healthbarFillTex->loadFromFile("Art/UI/HealthBarFill.png");
	fill.setTexture(healthbarFillTex);
}

void Healthbar::Update(sf::RectangleShape player, float value)
{
	UIComponent::CanUpdate(player);
	fill.setScale(value / maxHealth, 1);
	fill.setPosition(box.getPosition());

	//std::cout << player->GetHealth() << std::endl;
}

void Healthbar::Draw(sf::RenderWindow& window)
{
	UIComponent::Draw(window);
	window.draw(fill);
}
