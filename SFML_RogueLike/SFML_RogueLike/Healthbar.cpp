#include "Healthbar.h"

Healthbar::Healthbar(sf::Vector2f pos, int playerHealth)
	:	UIComponent(sf::Vector2f(256, 56), pos),
		showBar(true)
{
	maxHealth = playerHealth;
	fill = sf::RectangleShape(sf::Vector2f(256, 56));
	fill.setOrigin(fill.getSize() / 2.0f);

	LoadTextures();
}

Healthbar::Healthbar(sf::Vector2f pos, int entityHealth, bool show)
	:	Healthbar(pos, entityHealth)
{
	showBar = show;
}

void Healthbar::LoadTextures()
{
	sf::Texture* healthbarTex = new sf::Texture();
	healthbarTex->loadFromFile("Art/UI/HealthBar.png");
	box.setTexture(healthbarTex);

	sf::Texture* healthbarFillTex = new sf::Texture();
	healthbarFillTex->loadFromFile("Art/UI/HealthBarFill.png");
	fill.setTexture(healthbarFillTex);
}

void Healthbar::Update(sf::RectangleShape entityBody, float value)
{
	UIComponent::CanUpdate(entityBody);
	fill.setScale(value / maxHealth, 1);
	fill.setPosition(box.getPosition());

}

void Healthbar::Draw(sf::RenderWindow& window)
{
	UIComponent::Draw(window);
	window.draw(fill);
}
