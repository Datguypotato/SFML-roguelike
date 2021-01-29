#pragma once
#include "UIComponent.h"
#include "Player.h"

class Healthbar : public UIComponent
{
public:
	Healthbar(sf::Vector2f size, sf::Vector2f pos, int playerHealth);

	void Update(sf::RectangleShape player, float value);

	void Draw(sf::RenderWindow& window);

protected:
	sf::RectangleShape fill;

	float maxHealth;
};

