#pragma once
#include <SFML/Graphics.hpp>

#include "Collider.h"
#include "Entity.h"
#include "Weapon.h"
#include "Inventory.h"
#include "Collectable.h"

class Player: public Entity
{
public:
	Player(std::vector<Animation*> animations, float speed, int attackDamage);
	~Player();

	Player* Clone() const;

	void Update(float deltaTime) override;
	void Draw(sf::RenderWindow& window);
	void CollectItem(Collectable* c);

	Weapon* GetWeapon() { return weapon; }
	Inventory* GetInventory() { return inventory; }
private:
	Weapon* weapon;
	Inventory* inventory;

	sf::Vector2f attackBoxOffset;
};