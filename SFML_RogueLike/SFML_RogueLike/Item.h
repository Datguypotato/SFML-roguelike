#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Item
{
public:
	Item(sf::Texture* itemText);
	Item(sf::Texture* itemText, std::string name);

	void SetPosition(sf::Vector2f pos);

	void Draw(sf::RenderWindow& window);

	sf::RectangleShape GetItemBox() { return itemBox; }
	sf::Texture* GetItemTexture() { return itemTexture; }
	std::string GetName() { return itemName; }

protected:
	sf::RectangleShape itemBox;
	sf::Texture* itemTexture;

	std::string itemName;
};

