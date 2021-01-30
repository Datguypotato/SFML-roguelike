#pragma once
#include "UIComponent.h"
#include "Player.h"

class Healthbar : public UIComponent
{
public:
	Healthbar(sf::Vector2f pos, int playerHealth);
	Healthbar(sf::Vector2f pos, int playerHealth, bool show);

	void LoadTexture();
	void Update(sf::RectangleShape player, float value);
	void Draw(sf::RenderWindow& window);

	void SetShowBar(bool b) { showBar = b; }
	bool GetShowBarStatus() { return showBar; }
protected:
	sf::RectangleShape fill;

	bool showBar;
	float maxHealth;
};

