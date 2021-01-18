#pragma once
#include "Healthbar.h"
class Armourbar :
    public Healthbar
{
public:
	Armourbar(sf::Vector2f size, sf::Vector2f pos, int playerHealth);

	void Update(sf::RectangleShape player, float value);

	void Draw(sf::RenderWindow& window);
};

