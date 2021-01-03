#pragma once
#include <SFML/Graphics.hpp>

#include "Collider.h"
#include "Entity.h"
#include "Weapon.h"

class Player: public Entity
{
public:
	Player(std::vector<Animation*> animations, float speed, int attackDamage);
	~Player();

	Player* Clone() const;

	void Update(float deltaTime) override;
	void Draw(sf::RenderWindow& window);

	Weapon* GetWeapon() { return weapon; }
private:
	Weapon* weapon;
};