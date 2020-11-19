#pragma once
#include <SFML/Graphics.hpp>
#include <string.h>;



class UIComponent
{
public:
	UIComponent(sf::Vector2f size);
	~UIComponent();

	bool CursorIsInBox(sf::Vector2f mousePos);
	void SetPosition(sf::Vector2f pos) { box.setPosition(pos); }

	void Draw(sf::RenderWindow& window);

protected:
	sf::RectangleShape box;
	sf::Vector2f halfSize;
};

