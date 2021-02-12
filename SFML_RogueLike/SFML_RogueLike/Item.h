#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

#include "Entity.h"

enum class SlotRegion
{
	none,
	Weapon,
	body,
	legs
};

enum class Synergy
{
	red,
	blue,
	green
};

class Item
{
public:
	Item(sf::Texture* itemText);
	Item(sf::Texture* itemText, std::string name);
	Item(sf::Texture* itemText, std::string name, SlotRegion* sr);
	Item(sf::Texture* itemText, std::string name, SlotRegion* sr, Item* upgrade);


	virtual Item* Clone() { return new Item(*this); }

	virtual void Update(float deltaTime) {}

	void Draw(sf::RenderWindow& window);
	void SetPosition(sf::Vector2f pos);

	sf::RectangleShape GetItemBox() { return itemBox; }
	std::string GetName() { return itemName; }
	SlotRegion GetSlotRegion() { return *slotRegion; }
	Item* GetUpgrade() { return upgradeItem; }
	Synergy* GetSynergy() { return synergy; }

	virtual std::string GetItemStats();
	std::string GetItemStatsFormatted();

protected:

	sf::RectangleShape itemBox;
	std::string itemName;
	SlotRegion* slotRegion;
	Synergy* synergy;

	Item* upgradeItem;
};