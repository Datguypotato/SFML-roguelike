#pragma once
#include <SFML/Graphics.hpp>

#include "Collider.h"
#include "Entity.h"
#include "Weapon.h"
#include "Armour.h"
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

	void CheckCollision(std::vector<Entity*> enemies);
	void OnHit(const int damage, Entity* damageDealer) override;

	Weapon* GetWeapon() { return weapon; }
	Armour* GetArmour() { return armour; }
	Inventory* GetInventory() { return inventory; }
private:
	Weapon* weapon;
	Armour* armour;
	Inventory* inventory;

	sf::Vector2f facingDirection;
	sf::Vector2f lastFacingDir;
	sf::Vector2f attackBoxOffset;
};