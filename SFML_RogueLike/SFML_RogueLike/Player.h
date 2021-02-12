#pragma once
#include <SFML/Graphics.hpp>

#include "Collider.h"
#include "Entity.h"
#include "Weapon.h"
#include "Armour.h"
#include "LegArmour.h"
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
	void CollectItem(Item* i);

	void CheckCollision(std::vector<Entity*> enemies);
	void OnHit(const int damage, Entity* damageDealer) override;

	Weapon* GetWeapon() { return weapon; }
	Armour* GetArmour() { return armour; }
	LegArmour* GetLegArmour() { return legArmour; }
	Inventory* GetInventory() { return inventory; }

	SynergyManager* GetSynergyManager() { return synergyManager; }
	sf::Vector2i GetGridPosition() { return static_cast<sf::Vector2i>(body.getPosition()); }
private:
	Weapon* weapon;
	Armour* armour;
	LegArmour* legArmour;
	Inventory* inventory;
	SynergyManager* synergyManager;

	sf::Vector2f facingDirection;
	sf::Vector2f lastFacingDir;
	sf::Vector2f attackBoxOffset;

	sf::SoundBuffer playerAttackSFX;
	sf::SoundBuffer playerMissSFX;

	sf::Vector2i lastGridPosition;
};