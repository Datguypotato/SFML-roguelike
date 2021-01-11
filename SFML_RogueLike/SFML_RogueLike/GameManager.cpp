#include "GameManager.h"

GameManager::GameManager()
	:	player(BuildPlayer()),
		totalTime(0),
		timedEvents()
{
	window = new sf::RenderWindow(sf::VideoMode(1280, 720), "Super awesome game", sf::Style::Close | sf::Style::Resize);
	view = new sf::View(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(1280.0f, 720.0f));;
	levelmanager = new LevelManager(std::bind(&GameManager::NextLevel, this),  player);
	em = new EnemiesManager(player); 
	healthbar = new Healthbar(sf::Vector2f(256, 56), sf::Vector2f(500, 300), player->GetHealth());

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
	levelmanager->GetCurrentLevel()->Load(player, em);

	for (int i = 0; i < 4; i++)
	{
		lm->BuildKnife(em->RandomPos());
	}
	sf::Font* font = new sf::Font();
	font->loadFromFile("Fonts/04B_30.ttf");;
}

void GameManager::Update(float deltaTime)
{
	totalTime += deltaTime;
	player->Update(deltaTime);
	healthbar->Update(player);
	bagIcon->CanUpdate(*player->GetBody());

	sf::Vector2f mousepos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
	if (bagIcon->CursorIsInBox(mousepos))
		bagIcon->OnClick();

	player->GetInventory()->Update(mousepos, player->GetWeapon());
	em->Update(deltaTime);
	lm->Update(deltaTime);

	for (TimeEvent* e : timedEvents)
	{
		e->Tick(deltaTime);
	}
}

void GameManager::CheckCollision()
{
	std::vector<Enemy*> enemies = em->GetEnemies();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && player->GetWeapon()->CanAttack())
	{
		std::vector<Enemy*> enemies = em->GetEnemies();
		for (Enemy* enemy : enemies)
		{
			Collider eColl = enemy->GetCollider();
			if (player->GetWeapon()->GetAttackBox().CheckTrigger(eColl))
			{
				player->GetWeapon()->GetInRange()->push_back(enemy);
			}
		}
	}


	Collider pcoll = player->GetCollider();
	lm->CheckTrigger(player);

	//em->CheckCollision(player);

	levelmanager->GetCurrentLevel()->CheckCollision(pcoll);
	levelmanager->GetCurrentLevel()->CheckTrigger(pcoll, *em);
}

void GameManager::Draw()
{
	window->clear();

	levelmanager->GetCurrentLevel()->Draw(*window);
	lm->Draw(*window);
	player->Draw(*window);
	em->Draw(*window);
	healthbar->Draw(*window);
	bagIcon->Draw(*window);
	//window->draw(*testing);


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
	levelmanager->NextLevel(em);
	std::cout << "Player in door\n";
}

void GameManager::OpenInventory()
{
	std::cout << "inventory open\n";
}