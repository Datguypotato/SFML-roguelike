#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Item
{
public:
	Item(sf::Texture* itemText);
	Item(sf::Texture* itemText, std::string name);

	~Item();

	void SetPosition(sf::Vector2f pos);

	void Draw(sf::RenderWindow& window);

	sf::RectangleShape GetItemBox() { return itemBox; }
	std::string GetName() { return itemName; }

protected:
	sf::RectangleShape itemBox;

	std::string itemName;
};

