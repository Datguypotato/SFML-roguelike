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

void ButtonClicked(sf::RectangleShape box);


void ButtonClicked(sf::RectangleShape box)
{
	box.setFillColor(sf::Color::Blue);
	std::cout << "Button has been clicked\n";	
}

int main()
{

#pragma region UI
	sf::Font font;
	font.loadFromFile("Fonts/04B_30.TTF");
	sf::Text testingText;
	testingText = sf::Text("button", font, 10);
	testingText.setFillColor(sf::Color::Blue);

#pragma endregion

	//std::vector<Animation*> slimeAnimations = std::vector<Animation*>();
	//sf::Texture slimeDefault = sf::Texture();
	//sf::Texture slimeJump = sf::Texture();
	//sf::Texture slimeAir = sf::Texture();
	//sf::Texture slimeHit = sf::Texture();
	//sf::Texture slimeBite = sf::Texture();

	//slimeDefault.loadFromFile("Art/SlimeDefault.png");
	//slimeJump.loadFromFile("Art/SlimeJump.png");
	//slimeAir.loadFromFile("Art/SlimeInAir.png");
	//slimeHit.loadFromFile("Art/SlimeHit.png");	

	//slimeAnimations.push_back(new Animation(&slimeDefault, 8, 0.05f, "Default"));
	//slimeAnimations.push_back(new Animation(&slimeJump, 3, 0.2f, "Jump"));
	//slimeAnimations.push_back(new Animation(&slimeAir, 1, 0.2f, "Air"));
	//slimeAnimations.push_back(new Animation(&slimeHit, 6, 0.2f, "Hit"));

	//SlimeBoss* slimeboss = new SlimeBoss(slimeAnimations, sf::Vector2f(500, 500), player.GetBody());

	std::vector<Entity*> entities;
	//entities.push_back(&player);
	//entities.push_back(slimeboss);

	float deltaTime = 0.0f;
	sf::Clock clock;


	GameManager* game = GameManager::GetInstance();

	game->Start();


	while (game->GetWindow()->isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		if (deltaTime > 1.0f / 20.0f)
			deltaTime = 1.0f / 20.0f;

		sf::Event evnt;
		while (game->GetWindow()->pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				game->GetWindow()->close();
				break;
			case sf::Event::Resized:
				game->ResizeView();
			}
		}

		// testing ui
		//float aspectRatio = float(window.getSize().x / float(window.getSize().y));
		//button.SetPosition(sf::Vector2f(0, 100) + player->GetPosition());

		//sf::Vector2f mousepos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
		//if (button.CursorIsInBox(mousepos))
		//	button.OnClick();

		game->Update(deltaTime);
		game->CheckCollision();
		game->Draw();		
	}

	return 0;
}