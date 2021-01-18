#pragma once
#include "WeaponItem.h"


class Shield : public WeaponItem
{
public:
	Shield(sf::Texture* itemText, std::string name);
	Shield(sf::Texture* itemText, std::string name, Item* upgrade);

	void OnAttack(sf::Vector2f startingPos, sf::Vector2f direction) override;
	int OnHit(Entity* entity) override;
	std::string GetItemStats() override;

protected:
	void UnShield();

	float stunTime = 2.0f;
};