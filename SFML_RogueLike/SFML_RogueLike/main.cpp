#include <SFML/Graphics.hpp>
#include <iostream>
#include "tileson.hpp"
#include <string.h>

#include <EnemiesManager.h>
#include <Player.h>
#include <Slime.h>
#include <Ground.h>
#include <Collider.h>
#include <Button.h>
#include <Wall.h>
#include <Level.h>

static const float VIEW_HEIGHT = 720.0f;
static const float SLIME_SPAWN_TIMERMAX = 3.0f;

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
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Super awesome game", sf::Style::Close | sf::Style::Resize);
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(1280.0f, 720.0f));

#pragma region UI
	sf::Font font;
	font.loadFromFile("Fonts/04B_30.TTF");
	sf::Text testingText;
	testingText = sf::Text("button", font, 10);
	testingText.setFillColor(sf::Color::Blue);

	Button button = Button(sf::Vector2f(200, 100), window.mapPixelToCoords(sf::Vector2i(0, 0)), std::function(ButtonClicked));
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

	Player* player = new Player(playerAnimations, 250.0f);

	std::vector<Entity*> entities;
	entities.push_back(player);

	float deltaTime = 0.0f;
	sf::Clock clock;

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

	std::vector<Ground> Floor;
	std::vector<Wall> wall;

	Level testLevel = Level(tileSet, fs::path("../SFML_RogueLike/Art/World/Test.json"));

	testLevel.Load();

#pragma endregion

	EnemiesManager em = EnemiesManager(&player->GetCollider().GetBody(), &entities);

	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		if (deltaTime > 1.0f / 20.0f)
			deltaTime = 1.0f / 20.0f;

		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				ResizeView(window, view);
			}
		}

		sf::Vector2f direction;

		view.setCenter(player->GetPosition());

		float aspectRatio = float(window.getSize().x / float(window.getSize().y));
		button.SetPosition(sf::Vector2f(0, 100) + player->GetPosition());

		sf::Vector2f mousepos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
		if (button.CursorIsInBox(mousepos))
			button.OnClick();


		window.clear();


		Collider pcoll = player->GetCollider();
		testLevel.CheckCollision(pcoll);
		testLevel.CheckTrigger(pcoll);
		testLevel.Draw(window);

		for (Entity* entity : entities)
		{
			entity->Draw(window);
			entity->Update(deltaTime);
		}
		em.Update(deltaTime);


		window.setView(view);
		window.display();
	}

	return 0;
}
