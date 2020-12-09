#include <SFML/Graphics.hpp>
#include <iostream>
#include <tileson.hpp>
#include <string.h>
#include <cmath>

#include "GameManager.h"
#include "EnemiesManager.h"
#include "Player.h"
#include "Slime.h"
#include "Goblin.h"
#include "Ghost.h"
#include "SlimeBoss.h"

#include "Ground.h"
#include "Collider.h"
#include "Button.h"
#include "Wall.h"
#include "Level.h"
#include "LevelManager.h"

static const float VIEW_HEIGHT = 720.0f;
static const float SLIME_SPAWN_TIMERMAX = 3.0f;

LevelManager* levelManager;

void NextLevel();
void ButtonClicked(sf::RectangleShape box);
void ResizeView(const sf::RenderWindow& window, sf::View& view);

void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
	float aspectRatio = float(window.getSize().x / float(window.getSize().y));

	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

void ButtonClicked(sf::RectangleShape box)
{
	box.setFillColor(sf::Color::Blue);
	std::cout << "Button has been clicked\n";	
}

int main()
{
	//sf::RenderWindow window(sf::VideoMode(1280, 720), "Super awesome game", sf::Style::Close | sf::Style::Resize);
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(1280.0f, 720.0f));

#pragma region UI
	sf::Font font;
	font.loadFromFile("Fonts/04B_30.TTF");
	sf::Text testingText;
	testingText = sf::Text("button", font, 10);
	testingText.setFillColor(sf::Color::Blue);

	//Button button = Button(sf::Vector2f(200, 100), window.mapPixelToCoords(sf::Vector2i(0, 0)), std::function(ButtonClicked));
#pragma endregion

	// load player textures
	std::vector<Animation*> playerAnimations;
	sf::Texture playerDefault;
	sf::Texture playerWalk;
	sf::Texture playerJump;
	sf::Texture playerAttack;

	playerDefault.loadFromFile("Art/PlayerDefault.png");
	playerWalk.loadFromFile("Art/PlayerWalk.png");
	playerAttack.loadFromFile("Art/PlayerAttack.png");

	playerAnimations.push_back(new Animation(&playerDefault, 7, 0.25f, "Default"));
	playerAnimations.push_back(new Animation(&playerWalk, 12, 0.12f, "Walk"));
	playerAnimations.push_back(new Animation(&playerAttack, 9, 0.035f, "Attack"));

	Player player = Player(playerAnimations, 250.0f);

	std::vector<Animation*> slimeAnimations = std::vector<Animation*>();
	sf::Texture slimeDefault = sf::Texture();
	sf::Texture slimeJump = sf::Texture();
	sf::Texture slimeAir = sf::Texture();
	sf::Texture slimeHit = sf::Texture();
	sf::Texture slimeBite = sf::Texture();

	slimeDefault.loadFromFile("Art/SlimeDefault.png");
	slimeJump.loadFromFile("Art/SlimeJump.png");
	slimeAir.loadFromFile("Art/SlimeInAir.png");
	slimeHit.loadFromFile("Art/SlimeHit.png");	

	slimeAnimations.push_back(new Animation(&slimeDefault, 8, 0.05f, "Default"));
	slimeAnimations.push_back(new Animation(&slimeJump, 3, 0.2f, "Jump"));
	slimeAnimations.push_back(new Animation(&slimeAir, 1, 0.2f, "Air"));
	slimeAnimations.push_back(new Animation(&slimeHit, 6, 0.2f, "Hit"));

	SlimeBoss* slimeboss = new SlimeBoss(slimeAnimations, sf::Vector2f(500, 500), player.GetBody());

	std::vector<Entity*> entities;
	entities.push_back(&player);
	entities.push_back(slimeboss);

	float deltaTime = 0.0f;
	sf::Clock clock;

	EnemiesManager em = EnemiesManager(player.GetBody(), &entities);

#pragma region  Level gen
	std::map<int, sf::Texture*> tileSet;
	sf::Texture groundtexture;
	sf::Texture oldGround;
	sf::Texture door;
	groundtexture.loadFromFile("Art/World/GrassTopDown.png");
	oldGround.loadFromFile("Art/World/GrassGround.png");
	door.loadFromFile("Art/World/door.png");
	tileSet.insert(std::pair(0, &groundtexture));
	tileSet.insert(std::pair(1, &oldGround));
	tileSet.insert(std::pair(2, &door));

	std::vector<fs::path> paths;
	paths.push_back("../SFML_RogueLike/Art/World/Test.json");
	paths.push_back("../SFML_RogueLike/Art/World/Test2.json");

	levelManager = new LevelManager(tileSet, paths, NextLevel, &player, &em);
	GameManager game = GameManager(view, player, *levelManager);
	levelManager->GetCurrentLevel()->Load(&player);

#pragma endregion



	while (game.GetWindow()->isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		if (deltaTime > 1.0f / 20.0f)
			deltaTime = 1.0f / 20.0f;

		sf::Event evnt;
		while (game.GetWindow()->pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				game.GetWindow()->close();
				break;
			case sf::Event::Resized:
				game.ResizeView(*game.GetWindow(), view);
			}
		}
		//levelManager->CenterRectangleShape(player->GetPosition());

		// testing ui
		//float aspectRatio = float(window.getSize().x / float(window.getSize().y));
		//button.SetPosition(sf::Vector2f(0, 100) + player->GetPosition());

		//sf::Vector2f mousepos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
		//if (button.CursorIsInBox(mousepos))
		//	button.OnClick();

		game.Update(deltaTime);
		game.CheckCollision();
		game.Draw();		
		//Collider pcoll = player->GetCollider();
		//levelManager->GetCurrentLevel()->CheckCollision(pcoll);
		//levelManager->GetCurrentLevel()->CheckTrigger(pcoll);
		//levelManager->GetCurrentLevel()->Draw(window);
		//levelManager->Update(deltaTime);

		//for (Entity* entity : entities)
		//{
		//	entity->Draw(window);
		//	entity->Update(deltaTime);
		//	if (entity != player)
		//	{
		//		if (entity->GetCollider().CheckCollision(pcoll, 0.8f))
		//		{
		//			player->OnHit(10);
		//		}
		//	}
		//		
		//}
		////em.Update(deltaTime);
		//evelManager->Draw(window);

	}

	return 0;
}

void NextLevel()
{
	levelManager->NextLevel();
	std::cout << "Player in door\n";
}