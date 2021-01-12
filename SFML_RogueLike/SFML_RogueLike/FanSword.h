#pragma once
#include "Item.h"
#include "SlimeBall.h"

class FanSword : public Item
{
public:
	FanSword(sf::Texture* itemText, std::string name, SlotRegion* sr);
	FanSword(sf::Texture* itemText, std::string name, SlotRegion* sr, Item* upgrade);

	FanSword* Clone() override { return new FanSword(*this); };

	void Update(float deltaTime) override;
	void Draw(sf::RenderWindow& window) override;

	int OnAttack(sf::Vector2f startingPos, sf::Vector2f direction) override;
	std::string GetItemStats() override;

protected:
	SlimeBall* BuildWindSlash(sf::Vector2f dir, sf::Vector2f startingPos);

	std::vector<SlimeBall*> projectiles;

	int damage;
};

