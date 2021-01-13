#include "Collectable.h"

Collectable::Collectable(std::vector<Animation*> animations, sf::Vector2f pos, Item* i)
	:	Entity(sf::Vector2f(100, 100), 1, animations, 0, 0, "Collectable"),
		item(i)
{
	body.setPosition(pos);
	tempPos = pos;
	randomStartingPoint = rand() % 100 + 1;
}

void Collectable::Update(float deltaTime)
{
	Entity::Update(deltaTime);
	if (isAlive)
	{
		randomStartingPoint += deltaTime;
		Hover();

		AC.Play("Default", faceRight);
		AC.UpdateAnimation(deltaTime, faceRight);
		body.move(velocity * deltaTime);
		TextureBody.setPosition(body.getPosition());
	}
}

void Collectable::Hover()
{
	tempPos.y += sin(randomStartingPoint * verticalSpeed) * amplitude;
	body.setPosition(tempPos);
}

Item* Collectable::GetItem()
{
	isAlive = false;
	return item;
}
