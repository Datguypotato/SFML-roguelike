#pragma once
#include "WeaponItem.h"
#include "SlimeBall.h"

class FanSword : public WeaponItem
{
public:
	FanSword(sf::Texture* itemText, std::string name);
	FanSword(sf::Texture* itemText, std::string name, Item* upgrade);
	~FanSword() override;

	FanSword* Clone() override { return new FanSword(*this); };

	void OnAttack(sf::Vector2f startingPos, sf::Vector2f direction) override;
	void Update(float deltaTime) override;
	void CheckCollision(Entity* entity);

	virtual void OnHit(Entity* e, Entity* projectile);

	std::vector<Entity*> GetProjectiles() override;
	std::string GetItemStats() override;

protected:
	SlimeBall* BuildWindSlash(sf::Vector2f dir, sf::Vector2f startingPos);

	std::vector<Entity*> projectiles;
};
