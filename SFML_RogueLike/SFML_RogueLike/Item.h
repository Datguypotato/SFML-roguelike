#pragma once
#include <SFML/Graphics.hpp>
#include <string>

#include "BleedEffect.h"

enum class SlotRegion
{
	none,
	head,
	body,
	legs
};

class Item
{
public:
	Item(sf::Texture* itemText);
	Item(sf::Texture* itemText, std::string name);
	Item(sf::Texture* itemText, std::string name, EffectValue e, SlotRegion* sr);

	~Item();

	void SetPosition(sf::Vector2f pos);

	void Draw(sf::RenderWindow& window);

	sf::RectangleShape GetItemBox() { return itemBox; }
	std::string GetName() { return itemName; }
	EffectValue GetEffectValue() { return effectValue; }
	SlotRegion GetSlotRegion() { return *slotRegion; }

protected:
	sf::RectangleShape itemBox;
	std::string itemName;
	EffectValue effectValue;
	SlotRegion* slotRegion;
};