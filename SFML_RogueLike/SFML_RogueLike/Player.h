#pragma once
#include <SFML/Graphics.hpp>
#include "AnimatorController.h"
#include "Collider.h"
#include "Entity.h"

class Player: public Entity
{
public:
	Player(std::map<std::string, Animation*> animations, float speed);
	Player(const Player& rhs);
	~Player();

	Player* Clone() const;

	void Update(float deltaTime) override;

private:

};