#pragma once
#include "FanSword.h"

class WindSlasher : public FanSword
{
public:
	WindSlasher(sf::Texture* itemText, std::string name, SlotRegion* sr);

	WindSlasher* Clone() override { return new WindSlasher(*this); };

	void Update(float deltaTime) override;

	std::string GetItemStats() override;
};

