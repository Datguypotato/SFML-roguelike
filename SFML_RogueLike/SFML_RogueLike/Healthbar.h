#pragma once
#include "UIComponent.h"
#include "Player.h"

class Healthbar : public UIComponent
{
public:
	Healthbar(sf::Vector2f pos, int entityHealth);
	Healthbar(sf::Vector2f pos, int entityHealth, bool show);
	void LoadTextures();

	void Update(sf::RectangleShape player, float value);
	void Draw(sf::RenderWindow& window);

	void SetBar(bool b) { showBar = b; }

protected:
	sf::RectangleShape fill;

	float maxHealth;
	bool showBar;
};

