#include "EnemiesManager.h"

EnemiesManager::EnemiesManager(Player* player)
	:	player(player),
		playerBody(player->GetBody())
{
}

EnemiesManager::~EnemiesManager()
{
}

void EnemiesManager::Update(float deltaTime)
{
	for (Enemy* enemy : enemies)
	{
		enemy->Update(deltaTime);
	}
}

void EnemiesManager::CheckCollision(Entity* player)
{
	for (Enemy* enemy : enemies)
	{
		Collider pcoll = player->GetCollider();
		if (enemy->GetCollider().CheckCollision(pcoll, 0.8f))
			player->OnHit(enemy->GetAttackDamage());
	}
}

void EnemiesManager::Draw(sf::RenderWindow& window)
{
	for (Enemy* enemy : enemies)
	{
		enemy->Draw(window);
	}
}

sf::Vector2f EnemiesManager::RandomPos()
{
	float randomX = 100 + (rand() % 1000);
	float randomY = 100 + (rand() % 1000);


	int randomId = rand() % 3;

	return sf::Vector2f(randomX, randomY);
}

Slime* EnemiesManager::BuildSlime(sf::Vector2f spawnPos, std::vector<TimeEvent*>* e)
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

	Slime* temp = new Slime(slimeAnimations, spawnPos, player);
	enemies.push_back(temp);
	for (TimeEvent* event : temp->GetEvents())
		e->push_back(event);

	return temp;
}

Goblin* EnemiesManager::BuildGoblin(sf::Vector2f spawnPos, std::vector<TimeEvent*>* e)
{
	// TODO Need to make the other art assets
	std::vector<Animation*> goblinAnimations;
	sf::Texture* goblinDefault = new sf::Texture();

	goblinDefault->loadFromFile("Art/Evilmerchant.png");
	goblinAnimations.push_back(new Animation(goblinDefault, 1, 0.25f, "Default"));

	Goblin* temp = new Goblin(goblinAnimations, spawnPos, player);
	enemies.push_back(temp);
	for (TimeEvent* event : temp->GetEvents())
		e->push_back(event);

	return temp;
}

Ghost* EnemiesManager::BuildGhost(sf::Vector2f spawnPos, std::vector<TimeEvent*>* e)
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

	Ghost* temp = new Ghost(ghostAnimations, spawnPos, player);
	enemies.push_back(temp);
	for (TimeEvent* event : temp->GetEvents())
		e->push_back(event);

	return temp;
}