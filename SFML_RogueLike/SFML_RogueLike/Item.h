#pragma once
#include <SFML/Graphics.hpp>
#include <string>

#include "BleedEffect.h"

class Item
{
public:
	Item(sf::Texture* itemText);
	Item(sf::Texture* itemText, std::string name);
	Item(sf::Texture* itemText, std::string name, EffectValue e);

	~Item();

	void SetPosition(sf::Vector2f pos);

	void Draw(sf::RenderWindow& window);

	sf::RectangleShape GetItemBox() { return itemBox; }
	std::string GetName() { return itemName; }
	EffectValue GetEffectValue() { return effectValue; }

protected:
	sf::RectangleShape itemBox;
	std::string itemName;
	EffectValue effectValue;
};