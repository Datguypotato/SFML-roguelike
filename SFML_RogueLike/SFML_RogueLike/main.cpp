#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <Player.h>
#include <Platform.h>
#include <Collider.h>

static const float VIEW_HEIGHT = 720.0f;

void ResizeView(const sf::RenderWindow& window, sf::View& view);

void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
	float aspectRatio = float(window.getSize().x / float(window.getSize().y));

	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Hello world", sf::Style::Close | sf::Style::Resize);
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(1280.0f, 720.0f));

	sf::Texture groundtexture;
	groundtexture.setRepeated((true));
	groundtexture.loadFromFile("Art/GrassGround.png");

	// load player textures
	std::map<std::string, Animation*> playerAnimations;
	sf::Texture playerDefault;
	sf::Texture playerWalk;
	sf::Texture playerJump;
	sf::Texture playerAttack;

	playerDefault.loadFromFile("Art/PlayerDefault.png");
	playerWalk.loadFromFile("Art/PlayerWalk.png");
	playerJump.loadFromFile("Art/PlayerJump.png");
	playerAttack.loadFromFile("Art/PlayerAttack.png");

	playerAnimations.insert(std::pair<std::string, Animation*>("Default", &Animation(&playerDefault, 7, 0.25f)));
	playerAnimations.insert(std::pair<std::string, Animation*>("Walk", &Animation(&playerWalk, 12, 0.12f)));
	playerAnimations.insert(std::pair<std::string, Animation*>("Jump", &Animation(&playerJump, 4, 0.2f)));
	playerAnimations.insert(std::pair<std::string, Animation*>("Attack", &Animation(&playerAttack, 9, 0.035f)));

	sf::Sprite Ground;
	Ground.setTexture(groundtexture);

	Player* player = new Player(playerAnimations, 7, 0.08f, 250.0f, 200.0f);

	std::vector<Platform> platforms;

	platforms.push_back(Platform(&groundtexture, sf::Vector2f(400, 200), sf::Vector2f(500, 0)));
	platforms.push_back(Platform(&groundtexture, sf::Vector2f(400, 200), sf::Vector2f(500, 200)));
	platforms.push_back(Platform(Ground, sf::Vector2f(1280.0f, 128.0f), sf::Vector2f(0.0f, 500.0f)));

	float deltaTime = 0.0f;
	sf::Clock clock;


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
		

		player->Update(deltaTime);
		Collider playerCollider = player->GetCollider();

		sf::Vector2f direction;

		for (Platform& platform : platforms)
			if (platform.GetCollider().CheckCollision(playerCollider, 1.0f, direction))
				player->OnCollision(direction);

		view.setCenter(player->GetPosition());

		window.clear();
		player->Draw(window);
		window.setView(view);
		for (Platform& platform : platforms)
			platform.Draw(window);
		//window.draw(testGround);
		window.display();
	}

	return 0;
}