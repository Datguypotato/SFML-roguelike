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

class Item
{
public:
	Item(sf::Texture* itemText);
	Item(sf::Texture* itemText, std::string name);
	Item(sf::Texture* itemText, std::string name, SlotRegion* sr);
	Item(sf::Texture* itemText, std::string name, SlotRegion* sr, Item* upgrade);

	//TODO virtual Copy constructor
	virtual Item* Clone() { return new Item(*this); }

	~Item();

	virtual void Update(float deltaTime) {}

	virtual int OnHit(Entity* entity) { return 0; }
	virtual int OnAttack(sf::Vector2f startingPos, sf::Vector2f direction) { return 0; }

	virtual void Draw(sf::RenderWindow& window);
	void SetPosition(sf::Vector2f pos);

	sf::RectangleShape GetItemBox() { return itemBox; }
	std::string GetName() { return itemName; }
	SlotRegion GetSlotRegion() { return *slotRegion; }
	Item* GetUpgrade() { return upgradeItem; }
	virtual std::string GetItemStats();

protected:
	sf::RectangleShape itemBox;
	std::string itemName;
	SlotRegion* slotRegion;

	Item* upgradeItem;
};