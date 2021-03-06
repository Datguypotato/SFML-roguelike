#include "Entity.h"

Entity::Entity(sf::Vector2f textureSize, sf::Vector2f bodySize, int health, std::vector<Animation*> animations, float speed, int attackDamage, std::string n)
	:	faceRight(true),
		isAlive(true),
		AC(animations),
		damageCooldown(1.0f),
		damageCooldownMax(damageCooldown),
		playName("Default"),
		attackDamage(attackDamage),
		effecthandler(new EffectHandler()),
		events(std::vector<TimeEvent*>()),
		name(n)
{
	TextureBody.setSize(textureSize);
	TextureBody.setOrigin(TextureBody.getSize() / 2.0f);

	body.setSize(bodySize);
	body.setOrigin(body.getSize() / 2.0f);

	this->health = health;
	maxHealth = health;
	this->speed = speed;
	TextureBody.setTexture(AC.GetActiveAnimation()->GetTexture());

	sound = sf::Sound();
	sound.setVolume(05.0f);

	hitSound.loadFromFile("PlayerHit.wav");

	events.push_back(new TimeEvent(std::bind(&Entity::GetEffects, this), 1.0f, false, "Effect"));
}

Entity::Entity(sf::Vector2f bodySize, int health, std::vector<Animation*> animations, float speed, int attackDamage, std::string n)
	:	faceRight(true),
		isAlive(true),
		damageCooldown(1.0f),
		damageCooldownMax(damageCooldown),
		playName("Default"),
		attackDamage(attackDamage),
		AC(animations),
		effecthandler(new EffectHandler()),
		events(std::vector<TimeEvent*>()),
		name(n)
{
	TextureBody.setSize(bodySize);
	TextureBody.setOrigin(TextureBody.getSize() / 2.0f);

	body.setSize(bodySize);
	body.setOrigin(body.getSize() / 2.0f);

	this->health = health;
	maxHealth = health;
	this->speed = speed;
	TextureBody.setTexture(AC.GetActiveAnimation()->GetTexture());

	sound = sf::Sound();
	sound.setVolume(05.0f);
}

Entity::~Entity()
{
}

Entity::Entity(const Entity& rhs)
	:	isAlive(rhs.isAlive),
		faceRight(rhs.faceRight),
		AC(rhs.AC)
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

	for (TimeEvent* timeEvent : events)
	{
		timeEvent->Tick(deltaTime);
	}

	damageCooldown -= deltaTime;

	if (TextureBody.getTexture() != AC.GetActiveAnimation()->GetTexture())
		TextureBody.setTexture(AC.GetActiveAnimation()->GetTexture());

	if (TextureBody.getTextureRect() != AC.GetActiveAnimation()->uvRect)
		TextureBody.setTextureRect(AC.GetActiveAnimation()->uvRect);
}

void Entity::Draw(sf::RenderWindow& window)
{
	if(isAlive)
		window.draw(TextureBody);
}

void Entity::OnCollision(sf::Vector2f direction)
{
	if (isAlive)
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
}

void Entity::OnHit(const int damage, Entity* damageDealer)
{
	OnHit(damage);
}

void Entity::OnHit(const int damage)
{
	if (damageCooldown <= 0)
	{
		damageCooldown = damageCooldownMax;
		sound.setBuffer(hitSound);
		sound.play();

		std::cout << name << ": ";

		if (health - damage <= 0)
		{
			health = 0;
			isAlive = false;
			std::cout << "Lost " << damage << " hp " << name << " has " << health << " hp left\n";
			OnDeath();
		}
		else
		{
			health -= damage;
			std::cout << "Lost " << damage << " hp " << name << " has " << health << " hp left\n";
		}
	}
}

void Entity::Heal(int healValue)
{
	if (health + healValue >= maxHealth)
		health = maxHealth;
	else
		health += healValue;
}

void Entity::GetEffects()
{
	if(effecthandler->hasEffects())
		OnHit(effecthandler->GetBleedDamage(), nullptr);


}

TimeEvent* Entity::GetEvent(std::string n)
{
	for (TimeEvent* e : events)
	{
		if (e->GetEventName() == n)
		{
			return e;
		}
	}

	return nullptr;
}

void Entity::OnDeath()
{
	std::cout << "has died\n";
	sound.resetBuffer();
	for (TimeEvent* event : events)
		event->Pause();
}