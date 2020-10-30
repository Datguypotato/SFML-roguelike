#include "Entity.h"

Entity::Entity(sf::Vector2f textureSize, sf::Vector2f bodySize)
	:	faceRight(true)
{
	TextureBody.setSize(textureSize);
	TextureBody.setOrigin(TextureBody.getSize() / 2.0f);

	body.setSize(bodySize);
	body.setOrigin(body.getSize() / 2.0f);
}

Entity::~Entity()
{
}

void Entity::Update(float deltaTime)
{
	velocity.y += 981.0f * deltaTime;

	if (velocity.x != 0.0f)
	{
		if (velocity.x > 0.0f)
			faceRight = true;
		else
			faceRight = false;
	}
}

void Entity::Draw(sf::RenderWindow& window)
{
	window.draw(TextureBody);
}

void Entity::OnCollision(sf::Vector2f direction)
{
	if (direction.x < 0.0f)
	{
		// collision on the left
		velocity.x = 0.0f;
	}
	else if (direction.x > 0.0f)
	{
		// collision on the right
		velocity.x = 0.0f;
	}

	if (direction.y < 0.0f)
	{
		// collision down
		velocity.y = 0.0f;
	}
	else if (direction.y < 0.0f)
	{
		// collision up
		velocity.y = 0.0f;
	}
}
