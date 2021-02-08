#include "Player.h"

Player::Player(std::vector<Animation*> animations, float speed, int attackDamage)
	:	Entity(sf::Vector2f(50, 80), sf::Vector2f(50, 70), 100, animations, speed, attackDamage, "Player"),
		legArmour(new LegArmour()),	
		attackBoxOffset(sf::Vector2f(-body.getSize().x, 0)),
		facingDirection(sf::Vector2f(0,0)),
		lastFacingDir(sf::Vector2f(0,0))
{
	sf::Texture* texture = new sf::Texture();
	sf::Texture* texture2 = new sf::Texture();
	texture->loadFromFile("Art/AttackBox.png");
	texture2->loadFromFile("Art/WeaponSlash.png");
	std::vector<Animation*> weaponAnimations = std::vector<Animation*>();
	weaponAnimations.push_back(new Animation(texture, 2, 1.0f, "Default"));
	weaponAnimations.push_back(new Animation(texture2, 9, 0.02f, "Attack"));

	weapon = new Weapon(attackDamage, 2.0f, AnimatorController(weaponAnimations));
	armour = new Armour(weapon);
	synergyManager = new SynergyManager(weapon, armour);
	inventory = new Inventory(&body, weapon, armour, legArmour, synergyManager);
}

Player::~Player()
{
}

Player* Player::Clone() const
{
	return new Player(*this);
}

void Player::Update(float deltaTime)
{
	Entity::Update(deltaTime);
	weapon->Update(deltaTime);
	armour->Update(deltaTime);
	synergyManager->Update(deltaTime);

	std::string playName;

	facingDirection = sf::Vector2f(0, 0);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		velocity.x -= speed;
		attackBoxOffset = sf::Vector2f(body.getSize().x, 0);
		facingDirection += sf::Vector2f(-1, 0);
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		velocity.x += speed;
		attackBoxOffset = sf::Vector2f(-body.getSize().x, 0);
		facingDirection += sf::Vector2f(1, 0);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		velocity.y += speed;
		attackBoxOffset = sf::Vector2f(0, -body.getSize().y);
		facingDirection += sf::Vector2f(0, 1);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		velocity.y -= speed;
		attackBoxOffset = sf::Vector2f(0, body.getSize().y);
		facingDirection += sf::Vector2f(0, -1);
	}

	if (facingDirection == sf::Vector2f(0, 0))
		facingDirection = lastFacingDir;
	else
		lastFacingDir = facingDirection;



	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		armour->SetRoll();
	}

	armour->OnRoll(this, facingDirection);
	weapon->SetAttackBoxPos(body.getPosition() - attackBoxOffset);


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		AC.PlayNoInterupt("Attack", faceRight);
		legArmour->OnHit(*weapon->GetInRange());
		weapon->Attack(body.getPosition(), facingDirection);
		synergyManager->OnSuccesfullAttack();
	}

	if (velocity.x != 0.0f || velocity.y != 0.0f)
		playName = "Walk";
	else
		playName = "Default";
	
	AC.Play(playName, faceRight);
	AC.UpdateAnimation(deltaTime, faceRight);
	body.move(velocity * deltaTime);
	TextureBody.setPosition(body.getPosition());
}

void Player::Draw(sf::RenderWindow& window)
{
	Entity::Draw(window);
	inventory->Draw(window);
	weapon->Draw(window);
}

void Player::CollectItem(Collectable* c)
{
	if(!inventory->isFull())
		inventory->GetItem(c->GetItem());
}

void Player::CheckCollision(std::vector<Entity*> enemies)
{
	weapon->CheckCollision(enemies);
	armour->CheckCollision(enemies);
}

void Player::OnHit(const int damage, Entity* damageDealer)
{
	if (damageCooldown <= 0)
	{
		int dmg = damage; // so i can edit the value 

		weapon->OnHit(dmg);
		synergyManager->PlayerHit();

		dmg = armour->OnHit(damage, damageDealer, GetPosition());
		Entity::OnHit(dmg, damageDealer);
	}
}