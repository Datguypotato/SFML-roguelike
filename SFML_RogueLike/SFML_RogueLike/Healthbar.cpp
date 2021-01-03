#include "Healthbar.h"

Healthbar::Healthbar(sf::Vector2f size, sf::Vector2f pos, int playerHealth)
	:	UIComponent(size, pos)
{
	maxHealth = playerHealth;

	sf::Texture* healthbarTex = new sf::Texture();
	healthbarTex->loadFromFile("Art/UI/HealthBar.png");
	box.setTexture(healthbarTex);

	healthbarFill = sf::RectangleShape(size);
	healthbarFill.setOrigin(healthbarFill.getSize() / 2.0f);
	sf::Texture* healthbarFillTex = new sf::Texture();
	healthbarFillTex->loadFromFile("Art/UI/HealthBarFill.png");
	healthbarFill.setTexture(healthbarFillTex);
}

void Healthbar::Update(Player* player)
{
	UIComponent::CanUpdate(*player->GetBody());
	healthbarFill.setScale((float)player->GetHealth() / maxHealth, 1);
	healthbarFill.setPosition(box.getPosition());

	//std::cout << player->GetHealth() << std::endl;
}

void Healthbar::Draw(sf::RenderWindow& window)
{
	UIComponent::Draw(window);
	window.draw(healthbarFill);
}
