#pragma once
#include "WeaponItem.h"


class Shield : public WeaponItem
{
public:
	Shield(sf::Texture* itemText, std::string name);
	Shield(sf::Texture* itemText, std::string name, Item* upgrade);

	void OnAttack(sf::Vector2f startingPos, sf::Vector2f direction) override;

protected:
	void UnShield();
};