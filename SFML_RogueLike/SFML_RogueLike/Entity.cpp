#include "Entity.h"

Entity::Entity(sf::Vector2f textureSize, sf::Vector2f bodySize, int health, std::map<std::string, Animation*> animations)
	:	faceRight(true),
		isAlive(true),
		onGround(false),
		AC(animations)
{
	TextureBody.setSize(textureSize);
	TextureBody.setOrigin(TextureBody.getSize() / 2.0f);

	body.setSize(bodySize);
	body.setOrigin(body.getSize() / 2.0f);

	this->health = health;
	TextureBody.setTexture(AC.GetActiveAnimation()->GetTexture());
}

Entity::~Entity()
{
}

void Entity::Update(float deltaTime)
{
	//velocity.y += 981.0f * deltaTime;

	if (velocity.x != 0.0f)
	{
		if (velocity.x > 0.0f)
			faceRight = true;
		else
			faceRight = false;
	}


	if (TextureBody.getTexture() != AC.GetActiveAnimation()->GetTexture())
		TextureBody.setTexture(AC.GetActiveAnimation()->GetTexture());

	if (TextureBody.getTextureRect() != AC.GetActiveAnimation()->uvRect)
		TextureBody.setTextureRect(AC.GetActiveAnimation()->uvRect);
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
		onGround = true;
		velocity.y = 0.0f;
	}
	else if (direction.y < 0.0f)
	{
		// collision up
		velocity.y = 0.0f;
	}
}

void Entity::OnHit(int damage)
{
	if (health - damage <= 0)
	{
		health = 0;
		isAlive = false;
	}
	else
	{
		health -= damage;
	}
}