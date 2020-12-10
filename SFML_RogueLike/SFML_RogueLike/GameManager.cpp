#include "GameManager.h"

GameManager::GameManager()
	:	player(BuildPlayer()),
		totalTime(0)
{
	view = new sf::View(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(1280.0f, 720.0f));;
	window = new sf::RenderWindow(sf::VideoMode(1280, 720), "Super awesome game", sf::Style::Close | sf::Style::Resize);

	levelmanager = new LevelManager(std::bind(&GameManager::NextLevel, this),  player);
}

GameManager::~GameManager()
{
}

GameManager* GameManager::instance = 0;

GameManager* GameManager::GetInstance()
{
	if (!instance)
	{
		instance = new GameManager();
	}

	return instance;
}

void GameManager::ResizeView()
{
	float aspectRatio = float(window->getSize().x / float(window->getSize().y));

	view->setSize(720 * aspectRatio, 720);
}

void GameManager::Start()
{
	levelmanager->GetCurrentLevel()->Load(player);
}

void GameManager::Update(float deltaTime)
{
	totalTime += deltaTime;
	player->Update(deltaTime);

	for (Enemy enemy : enemies)
	{
		enemy.Update(deltaTime);
	}

}

void GameManager::CheckCollision()
{
	Collider pcoll = player->GetCollider();
	for (Enemy enemy : enemies)
	{
		if (enemy.GetCollider().CheckCollision(pcoll, 0.8f))
			player->OnHit(1);
	}

	levelmanager->GetCurrentLevel()->CheckCollision(pcoll);
	levelmanager->GetCurrentLevel()->CheckTrigger(pcoll);
}

void GameManager::Draw()
{
	window->clear();

	levelmanager->GetCurrentLevel()->Draw(*window);
	player->Draw(*window);

	for (Enemy enemy : enemies)
	{
		enemy.Draw(*window);
	}

	view->setCenter(player->GetPosition());
	window->setView(*view);
	window->display();
}

Player* GameManager::BuildPlayer()
{
	// load player textures
	std::vector<Animation*> playerAnimations = std::vector<Animation*>();
	sf::Texture* playerDefault = new sf::Texture();
	sf::Texture* playerWalk = new sf::Texture();
	sf::Texture* playerJump = new sf::Texture();
	sf::Texture* playerAttack = new sf::Texture();

	playerDefault->loadFromFile("Art/PlayerDefault.png");
	playerWalk->loadFromFile("Art/PlayerWalk.png");
	playerAttack->loadFromFile("Art/PlayerAttack.png");

	playerAnimations.push_back(new Animation(playerDefault, 7, 0.25f, "Default"));
	playerAnimations.push_back(new Animation(playerWalk, 12, 0.12f, "Walk"));
	playerAnimations.push_back(new Animation(playerAttack, 9, 0.035f, "Attack"));

	return new Player(playerAnimations, 250.0f);
}

void GameManager::NextLevel()
{
	levelmanager->NextLevel();
	std::cout << "Player in door\n";
}