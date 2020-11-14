#include "Entity.h"

Entity::Entity(sf::Vector2f textureSize, sf::Vector2f bodySize, int health, std::map<std::string, Animation*> animations, float speed)
	:	faceRight(true),
		isAlive(true),
		AC(animations)
{
	TextureBody.setSize(textureSize);
	TextureBody.setOrigin(TextureBody.getSize() / 2.0f);

	body.setSize(bodySize);
	body.setOrigin(body.getSize() / 2.0f);

	this->health = health;
	this->speed = speed;
	TextureBody.setTexture(AC.GetActiveAnimation()->GetTexture());

	sound = sf::Sound();
	sound.setVolume(50.0f);
}

Entity::~Entity()
{
}

Entity::Entity(const Entity& rhs)
	:	isAlive(rhs.isAlive),
		faceRight(rhs.faceRight),
		AC(*rhs.AC.Clone())
{
	TextureBody = rhs.TextureBody;
	body = sf::RectangleShape();
	health = rhs.health;
	speed = rhs.speed;
	sound = rhs.sound;

	TextureBody.setTexture(AC.GetActiveAnimation()->GetTexture());
}

void Entity::Update(float deltaTime)
{
	velocity.x *= 0.1f;
	velocity.y *= 0.1f;

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