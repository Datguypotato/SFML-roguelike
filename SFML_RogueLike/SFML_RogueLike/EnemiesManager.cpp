#include "EnemiesManager.h"

EnemiesManager::EnemiesManager(sf::RectangleShape* playerBody, std::vector<Entity*>* entities)
	:	currTimer(0.0f),
		maxTimer(6.0f)
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

		float randomX = 1 + (rand() % 1000);
		float randomY = 1 + (rand() % 1000);

		entities->push_back(BuildSlime(sf::Vector2f(randomX, randomY)));
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