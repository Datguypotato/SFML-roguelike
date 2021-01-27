#pragma once
#include "Item.h"

class WeaponItem : public Item
{
public:
	WeaponItem(sf::Texture* itemText, std::string name);
	WeaponItem(sf::Texture* itemText, std::string name, Item* upgrade);
	virtual ~WeaponItem() {}

	virtual WeaponItem* Clone() { return new WeaponItem(*this); }

	virtual void Update(float deltaTime) {}

	virtual int OnHit(Entity* entity) { return 0; }
	virtual void OnAttack(sf::Vector2f startingPos, sf::Vector2f direction) { }
	virtual void CheckCollision(Entity* entity) {}
	virtual bool SetEmpowerAttack(bool b) { return isEmpowered = b; }
	virtual bool GetEmpowerAttack() { return isEmpowered; }

	void SetBlock(bool b) { isBlocking = b; }
	bool GetBlock() { return isBlocking; }

	std::string GetItemStats() override;
	int GetAttackDamage() { return attackDamage; }
	float GetAttackTimerMax() { return minusAttackTimerMax; }

	virtual std::vector<Entity*> GetProjectiles() { return std::vector<Entity*>(); }
	void Draw(sf::RenderWindow& window);

protected:
	bool isBlocking;
	bool isEmpowered;

	int attackDamage = 0;
	float minusAttackTimerMax = 0;
};