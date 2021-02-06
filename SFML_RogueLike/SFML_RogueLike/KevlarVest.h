#pragma once
#include "ArmourItem.h"

class KevlarVest : public ArmourItem
{
public:
	KevlarVest(sf::Texture* itemText, std::string name, Item* upgrade);
	KevlarVest(sf::Texture* itemText, std::string name);

	KevlarVest* Clone() { return new KevlarVest(*this); }

	int OnDamaged(int damage, Entity* e, sf::Vector2f playerPos) override;

	void GainShield(int amount) override;
	int GetShield() override { return shieldAmount; }
	void SetShield(int amount) override { shieldAmount = amount; }

	int GetShieldMultiplier() { return shieldGainPerKill; }

	std::string GetItemStats() override;

protected:
	int shieldGainPerKill = 10;

	int shieldAmount = 0;
};

