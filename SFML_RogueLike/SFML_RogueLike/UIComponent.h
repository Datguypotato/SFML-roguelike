#pragma once
#include <SFML/Graphics.hpp>
#include <string.h>;

#include "Player.h"

class UIComponent
{
public:
	UIComponent(sf::Vector2f size, sf::Vector2f pos);
	~UIComponent();

	bool CursorIsInBox(sf::Vector2f mousePos);
	void CanUpdate(Player* player);
	virtual void Update(Player* player);
	void SetPosition(sf::Vector2f pos) { box.setPosition(pos); }

	void Draw(sf::RenderWindow& window);

	sf::Vector2f GetPosition() { return position; }
	sf::Vector2f GetSize() { return size; }

	bool GetDrawnStatus() { return isDrawing; }

protected:
	bool isDrawing;

	sf::RectangleShape box;

	sf::Vector2f size;
	sf::Vector2f halfSize;
	sf::Vector2f position;
};

