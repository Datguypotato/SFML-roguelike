#pragma once
#include "FanSword.h"

class WindSlasher : public FanSword
{
public:
	WindSlasher(sf::Texture* itemText, std::string name);

	WindSlasher* Clone() override { return new WindSlasher(*this); };

	void Update(float deltaTime) override;
	void OnHit(Entity* e, SlimeBall* projectile) override;

	std::string GetItemStats() override;

private:
};

