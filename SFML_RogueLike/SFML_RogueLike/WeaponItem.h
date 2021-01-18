#pragma once
#include "Item.h"

class WeaponItem : public Item
{
public:
	WeaponItem(sf::Texture* itemText, std::string name);
	WeaponItem(sf::Texture* itemText, std::string name, Item* upgrade);
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

	virtual void DrawProjectiles(sf::RenderWindow& window) {};
	void Draw(sf::RenderWindow& window);

protected:
	bool isBlocking;
	bool isEmpowered;
};