#include "EnemiesManager.h"

EnemiesManager::EnemiesManager(sf::RectangleShape* playerBody, std::vector<Entity*>* entities)
	:	currTimer(0.0f),
		maxTimer(2.0f)
{
	this->playerBody = playerBody;
	this->entities = entities;
}

EnemiesManager::~EnemiesManager()
{
}

void EnemiesManager::Update(float deltaTime)
{
	currTimer -= deltaTime;

	if (currTimer <= 0.0f)
	{
		currTimer = maxTimer - currTimer;

		float randomX = 100 + (rand() % 1000);
		float randomY = 100 + (rand() % 1000);


		int randomId = rand() % 3;

		switch (randomId)
		{
		case 0:
			entities->push_back(BuildSlime(sf::Vector2f(randomX, randomY)));
			break;
		case 1:
			entities->push_back(BuildGoblin(sf::Vector2f(randomX, randomY)));
			break;
		case 2:
			entities->push_back(BuildGhost(sf::Vector2f(randomX, randomY)));
			break;
		default:
			std::cout << "Unexpected int " << randomId << std::endl;
			break;
		}
		
		std::cout << "chosen random monster is " << randomId << std::endl;
	}
}

Slime* EnemiesManager::BuildSlime(sf::Vector2f spawnPos)
{
	// load slime textures
	std::vector<Animation*> slimeAnimations;
	sf::Texture* slimeDefault = new sf::Texture();
	sf::Texture* slimeJump = new sf::Texture();
	sf::Texture* slimeAir = new sf::Texture();
	sf::Texture* slimeHit = new sf::Texture();

	slimeDefault->loadFromFile("Art/SlimeDefault.png");
	slimeJump->loadFromFile("Art/SlimeJump.png");
	slimeAir->loadFromFile("Art/SlimeInAir.png");
	slimeHit->loadFromFile("Art/SlimeHit.png");

	slimeAnimations.push_back(new Animation(slimeDefault, 8, 0.05f, "Default"));
	slimeAnimations.push_back(new Animation(slimeJump, 3, 0.2f, "Jump"));
	slimeAnimations.push_back(new Animation(slimeAir, 1, 0.2f, "Air"));
	slimeAnimations.push_back(new Animation(slimeHit, 6, 0.2f, "Hit"));
	return new Slime(slimeAnimations, spawnPos, playerBody);
}

Goblin* EnemiesManager::BuildGoblin(sf::Vector2f spawnPos)
{
	// TODO Need to make the other art assets
	std::vector<Animation*> goblinAnimations;
	sf::Texture* goblinDefault = new sf::Texture();

	goblinDefault->loadFromFile("Art/Evilmerchant.png");
	goblinAnimations.push_back(new Animation(goblinDefault, 1, 0.25f, "Default"));

	return new Goblin(goblinAnimations, sf::Vector2f(1000, 1000), playerBody);
}

Ghost* EnemiesManager::BuildGhost(sf::Vector2f spawnPos)
{
	std::vector<Animation*> ghostAnimations;
	sf::Texture* ghostDefault = new sf::Texture();
	sf::Texture* ghostAttack = new sf::Texture();
	sf::Texture* ghostCharge = new sf::Texture();

	ghostDefault->loadFromFile("Art/GhostDefault.png");
	ghostAttack->loadFromFile("Art/GhostInAir.png");
	ghostCharge->loadFromFile("Art/GhostCharge.png");

	ghostAnimations.push_back(new Animation(ghostDefault, 9, 0.2f, "Default"));
	ghostAnimations.push_back(new Animation(ghostAttack, 27, 0.05f, "Attack"));
	ghostAnimations.push_back(new Animation(ghostCharge, 8, 0.2f, "Charge"));

	return new Ghost(ghostAnimations, sf::Vector2f(1000, 1000), playerBody);
}

