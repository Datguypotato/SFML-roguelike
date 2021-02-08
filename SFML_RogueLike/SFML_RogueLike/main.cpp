#include <SFML/Graphics.hpp>
#include <iostream>
#include <tileson.hpp>
#include <string.h>

#include "GameManager.h"

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
	srand(NULL);
	float deltaTime = 0.0f;
	sf::Clock clock;

	GameManager game = GameManager();
	game.Start();

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
				game.ResizeView();
			}
		}

		game.CheckCollision();
		game.Update(deltaTime);
		game.Draw();		
	}

	return 0;
}