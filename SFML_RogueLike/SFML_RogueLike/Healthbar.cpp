#include "Healthbar.h"

Healthbar::Healthbar(sf::Vector2f pos, int playerHealth)
	:	UIComponent(sf::Vector2f(256, 56), pos),
		showBar(true)
{
	maxHealth = (float)playerHealth;
	fill = sf::RectangleShape(sf::Vector2f(256, 56));
	fill.setOrigin(fill.getSize() / 2.0f);

	LoadTexture();
}

Healthbar::Healthbar(sf::Vector2f pos, int entityHealth, bool show)
	:	Healthbar(pos, entityHealth)
{
	sf::Vector2f size = sf::Vector2f(32, 7) * (float)entityHealth;

	box.setSize(size);
	box.setOrigin(size / 2.0f);

	fill.setSize(size);
	fill.setOrigin(size / 2.0f);

	LoadTexture();
}

void Healthbar::LoadTexture()
{
	sf::Texture* tex = new sf::Texture();
	tex->loadFromFile("Art/UI/HealthBar.png");
	box.setTexture(tex);

	tex = new sf::Texture();
	tex->loadFromFile("Art/UI/HealthBarFill.png");
	fill.setTexture(tex);
}

void Healthbar::Update(sf::RectangleShape player, float value)
{
	// TODO Set position of health bar
	UIComponent::CanUpdate(player);
	fill.setScale(value / maxHealth, 1);
	sf::Vector2f offset = sf::Vector2f(0, box.getSize().y);
	box.setPosition(player.getPosition() - position - offset);
	fill.setPosition(box.getPosition());

	//std::cout << player->GetHealth() << std::endl;
}

void Healthbar::Draw(sf::RenderWindow& window)
{
	UIComponent::Draw(window);
	window.draw(fill);
}
