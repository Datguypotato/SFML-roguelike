#include "GameManager.h"

GameManager::GameManager()
	:	totalTime(0),
		timedEvents()
{
	window = new sf::RenderWindow(sf::VideoMode(1280, 720), "Super awesome game", sf::Style::Close | sf::Style::Resize);
	view = new sf::View(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(1280.0f, 720.0f));;
	Player* temp = BuildPlayer();
	levelmanager = new LevelManager(std::bind(&GameManager::NextLevel, this), temp);
	em = new EnemiesManager(temp); 
	player = temp;
	healthbar = new Healthbar(sf::Vector2f(500, 300), player->GetHealth());
	armourbar = new Armourbar(sf::Vector2f(256, 56), sf::Vector2f(500, 300), player->GetHealth());

	sf::Texture* btext = new sf::Texture();
	btext->loadFromFile("Art/UI/BagIcon.png");
	bagIcon = new Button(sf::Vector2f(100, 100), sf::Vector2f(500, -300), std::bind(&Inventory::OpenClose, player->GetInventory()), btext);
	lm = new LootManager();

	timedEvents.push_back(bagIcon->GetEvent());
	timedEvents.push_back(player->GetInventory()->GetEvent());
}

void GameManager::ResizeView()
{
	float aspectRatio = float(window->getSize().x / float(window->getSize().y));

	view->setSize(720 * aspectRatio, 720);
}

void GameManager::Start()
{
	levelmanager->GetCurrentLevel()->Load(player, em, lm);
}

void GameManager::Update(float deltaTime)
{
	totalTime += deltaTime;
	player->Update(deltaTime);
	healthbar->Update(*player->GetBody(), player->GetHealth());

	if (player->GetArmour()->GetActiveArmour() != nullptr)
		armourbar->Update(*player->GetBody(), player->GetArmour()->GetActiveArmour()->GetShield());
	else
		armourbar->Update(sf::Vector2f(99999, 9999), 0);
	bagIcon->CanUpdate(*player->GetBody());

	sf::Vector2f mousepos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
	bagIcon->OnClick(mousepos);

	player->GetInventory()->Update(mousepos);
	em->Update(deltaTime);
	lm->Update(deltaTime);

	for (TimeEvent* e : timedEvents)
	{
		e->Tick(deltaTime);
	}
}

void GameManager::CheckCollision()
{
	std::vector<Entity*> enemies = em->GetAliveEnemies();

	player->CheckCollision(enemies);

	Collider pcoll = player->GetCollider();
	lm->CheckTrigger(player);

	em->CheckCollision(player);

	levelmanager->GetCurrentLevel()->CheckCollision(pcoll);
	levelmanager->GetCurrentLevel()->CheckTrigger(pcoll, *em);
}

void GameManager::Draw()
{
	window->clear();

	levelmanager->GetCurrentLevel()->Draw(*window);
	lm->Draw(*window);
	em->Draw(*window);
	player->Draw(*window);
	healthbar->Draw(*window);
	levelmanager->GetCurrentLevel()->LateDraw(*window);

	armourbar->Draw(*window);
	bagIcon->Draw(*window);


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

	playerAnimations.push_back(new Animation(playerWalk, 12, 0.12f, "Walk"));
	playerAnimations.push_back(new Animation(playerAttack, 9, 0.035f, "Attack"));
	playerAnimations.push_back(new Animation(playerDefault, 7, 0.25f, "Default"));

	Player* p = new Player(playerAnimations, 250.0f, 1);

	return p;
}

void GameManager::NextLevel()
{
	levelmanager->NextLevel(em, lm);
	std::cout << "Player in door\n";
}

void GameManager::OpenInventory()
{
	std::cout << "inventory open\n";
}