#pragma once
#include "UIComponent.h"
#include "Player.h"

class Healthbar : public UIComponent
{
public:
	Healthbar(sf::Vector2f size, sf::Vector2f pos, int playerHealth);

	void Update(Player* player);

	void Draw(sf::RenderWindow& window);

private:
	sf::RectangleShape healthbarFill;

	float maxHealth;
};

