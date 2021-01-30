#include "EnemiesManager.h"

EnemiesManager::EnemiesManager(Player* player)
	:	player(player),
		playerBody(player->GetBody()),
		boss(nullptr),
		enemiesData(std::vector<SpawnData*>()),
		enemies(std::vector<Entity*>())
{
}

EnemiesManager::~EnemiesManager()
{
}

void EnemiesManager::Update(float deltaTime)
{
	for (TimeEvent* timeEvent : timedEvents)
		timeEvent->Tick(deltaTime);


	for (unsigned int i = 0; i < enemiesData.size(); i++)
	{

		if (enemiesData[i] != nullptr)
		{
			enemiesData[i]->time -= deltaTime;

			if (enemiesData[i]->time <= 0)
			{
				switch (enemiesData[i]->type)
				{
				case EnemyType::Slime:
					BuildSlime(enemiesData[i]->spawnPos);
					break;
				case EnemyType::Goblin:
					BuildGoblin(enemiesData[i]->spawnPos);
					break;
				case EnemyType::Ghost:
					BuildGhost(enemiesData[i]->spawnPos);
					break;
				case EnemyType::SlimeBoss:
					BuildSlimeBoss(enemiesData[i]->spawnPos);
					break;
				default:
					std::cout << "Unknowmn EnemyType: " << i << std::endl;
					break;
				}

				delete enemiesData[i];
				enemiesData[i] = nullptr;
			}
		}
	}

	for (Entity* enemy : enemies)
	{
		if (enemy->GetAliveStatus() && !enemy->GetEffectHandler()->IsStunned())
		{
			if (!enemy->GetEffectHandler()->IsStunned())
			{
				enemy->Update(deltaTime);
				enemy->GetSound().setVolume(0.0f);
			}
			else
				enemy->GetSound().setVolume(100.0f);
		}

		if(enemy)
		enemy->GetEffectHandler()->CountDownStun(deltaTime);
	}

	if (boss != nullptr)
	{
		boss->Update(deltaTime);

		std::vector<SlimeBall*> p = boss->GetProjectiles();
		for (SlimeBall* ball : p)
		{
			ball->Update(deltaTime);
		}
	}

}

void EnemiesManager::CheckCollision(Entity* player)
{
	Collider pcoll = player->GetCollider();
	for (Entity* enemy : enemies)
	{
		if (enemy->GetAliveStatus())
		{
			if (enemy->GetCollider().CheckCollision(pcoll, 0.8f))
				player->OnHit(enemy->GetAttackDamage(), enemy);
		}
	}

	if (boss != nullptr)
	{
		if (boss->GetCollider().CheckCollision(pcoll, 1.0f))
			player->OnHit(boss->GetAttackDamage(), boss);

		std::vector<SlimeBall*> p = boss->GetProjectiles();
		for (SlimeBall* ball : p)
		{
			if (ball->GetCollider().CheckCollision(pcoll, 0.0f) && ball->GetAliveStatus())
			{
				player->OnHit(ball->GetAttackDamage(), ball);
				ball->SetAliveStatus(false);
			}
		}
	}
}

void EnemiesManager::Draw(sf::RenderWindow& window)
{
	for (Entity* enemy : enemies)
	{
		if(enemy->GetAliveStatus())
			enemy->Draw(window);
	}

	if (boss != nullptr)
	{
		boss->Draw(window);

		std::vector<SlimeBall*> p = boss->GetProjectiles();
		for (SlimeBall* ball : p)
		{
			ball->Draw(window);
		}
	}
}

sf::Vector2f EnemiesManager::RandomPos()
{
	float randomX = 100.0f + (rand() % 1000);
	float randomY = 100.0f + (rand() % 1000);


	int randomId = rand() % 3;

	return sf::Vector2f(randomX, randomY);
}

Slime* EnemiesManager::BuildSlime(sf::Vector2f spawnPos)
{
	// load slime textures
	std::vector<Animation*> slimeAnimations = LoadSlimeAnimation();

	Slime* temp = new Slime(slimeAnimations, spawnPos, player);
	enemies.push_back(temp);

	return temp;
}

Goblin* EnemiesManager::BuildGoblin(sf::Vector2f spawnPos)
{
	// TODO Need to make the other art assets
	std::vector<Animation*> goblinAnimations;
	sf::Texture* goblinDefault = new sf::Texture();

	goblinDefault->loadFromFile("Art/Evilmerchant.png");
	goblinAnimations.push_back(new Animation(goblinDefault, 1, 0.25f, "Default"));

	Goblin* temp = new Goblin(goblinAnimations, spawnPos, player);
	enemies.push_back(temp);

	return temp;
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

	Ghost* temp = new Ghost(ghostAnimations, spawnPos, player);
	enemies.push_back(temp);

	return temp;
}

SlimeBoss* EnemiesManager::BuildSlimeBoss(sf::Vector2f spawnPos)
{
	std::vector<Animation*> slimeAnimations = LoadSlimeAnimation();

	SlimeBoss* temp = new SlimeBoss(slimeAnimations, spawnPos, player);

	boss = temp;
	enemies.push_back(boss);

	return nullptr;
}

std::vector<Entity*> EnemiesManager::GetAliveEnemies()
{
	std::vector<Entity*> alive = std::vector<Entity*>();

	for (Entity* e : enemies)
	{
		if (e->GetAliveStatus())
			alive.push_back(e);
	}
	return alive;
}

std::vector<Animation*> EnemiesManager::LoadSlimeAnimation()
{
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

	return slimeAnimations;
}

void EnemiesManager::AddEnemyData(EnemyType et, float time, sf::Vector2f pos)
{
	enemiesData.push_back(new SpawnData(et, time, pos));
}

bool EnemiesManager::IsFinished()
{
	bool allDead = true;

	for (Entity* e : enemies)
	{
		if (e->GetAliveStatus())
			allDead = false;
	}

	return allDead;

}