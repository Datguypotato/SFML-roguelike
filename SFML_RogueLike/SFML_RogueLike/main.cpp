#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "tileson.hpp"
#include <Player.h>
#include <Platform.h>
#include <Collider.h>
#include <Slime.h>

static const float VIEW_HEIGHT = 720.0f;

void ResizeView(const sf::RenderWindow& window, sf::View& view);

void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
	float aspectRatio = float(window.getSize().x / float(window.getSize().y));

	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Super awesome game", sf::Style::Close | sf::Style::Resize);
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(1280.0f, 720.0f));

	sf::Texture groundtexture;
	groundtexture.setRepeated((true));
	groundtexture.loadFromFile("Art/World/GrassTopDown.png");

	// load player textures
	std::map<std::string, Animation*> playerAnimations;
	sf::Texture playerDefault;
	sf::Texture playerWalk;
	sf::Texture playerJump;
	sf::Texture playerAttack;

	playerDefault.loadFromFile("Art/PlayerDefault.png");
	playerWalk.loadFromFile("Art/PlayerWalk.png");
	playerAttack.loadFromFile("Art/PlayerAttack.png");

	playerAnimations.insert(std::pair<std::string, Animation*>("Default", &Animation(&playerDefault, 7, 0.25f)));
	playerAnimations.insert(std::pair<std::string, Animation*>("Walk", &Animation(&playerWalk, 12, 0.12f)));
	playerAnimations.insert(std::pair<std::string, Animation*>("Jump", &Animation(&playerJump, 4, 0.2f)));
	playerAnimations.insert(std::pair<std::string, Animation*>("Attack", &Animation(&playerAttack, 9, 0.035f)));

	// load slime textures
	std::map<std::string, Animation*> slimeAnimations;
	sf::Texture slimeDefault;
	sf::Texture slimeJump;
	sf::Texture slimeAir;
	sf::Texture slimeHit;

	slimeDefault.loadFromFile("Art/SlimeDefault.png");
	slimeJump.loadFromFile("Art/SlimeJump.png");
	slimeAir.loadFromFile("Art/SlimeInAir.png");
	slimeHit.loadFromFile("Art/SlimeHit.png");

	slimeAnimations.insert(std::pair<std::string, Animation*>("Default", &Animation(&slimeDefault, 8, 0.05f, "Default")));
	slimeAnimations.insert(std::pair<std::string, Animation*>("Jump", &Animation(&slimeJump, 3, 0.2f, "Jump")));
	slimeAnimations.insert(std::pair<std::string, Animation*>("Air", &Animation(&slimeAir, 1, 0.2f, "Air")));
	slimeAnimations.insert(std::pair<std::string, Animation*>("Hit", &Animation(&slimeHit, 6, 0.2f, "Hit")));

	sf::Sprite Ground;
	Ground.setTexture(groundtexture);

	Player* player = new Player(playerAnimations, 250.0f, 200.0f);
	Slime* slime = new Slime(slimeAnimations, sf::Vector2f(200, 50), &player->GetCollider().GetBody());

	std::vector<Entity*> entities;
	
	entities.push_back(slime);
	entities.push_back(player);

	std::vector<Platform> platforms;

	//for (int x = 0; x < 16; x++)
	//{
	//	for (int y = 0; y < 16; y++)
	//	{
	//		platforms.push_back(Platform(&groundtexture, sf::Vector2f(128, 128), sf::Vector2f(x * 128, y * 128)));
	//	}
	//}


	float deltaTime = 0.0f;
	sf::Clock clock;

	tson::Tileson t;
	std::unique_ptr<tson::Map> map = t.parse(fs::path("../SFML_RogueLike/Art/World/Test.json"));

	if (map->getStatus() == tson::ParseStatus::OK)
	{
		for (auto& layer : map->getLayers())
		{
			if (layer.getType() == tson::LayerType::TileLayer)
			{
				for (const auto& [id, obj] : layer.getTileObjects())
				{
					sf::Vector2f groundPos = sf::Vector2f(obj.getPosition().x, obj.getPosition().y);
					sf::Vector2f groundSize = sf::Vector2f(obj.getTile()->getTileSize().x, obj.getTile()->getTileSize().y);

					platforms.push_back(Platform(&groundtexture, groundSize, groundPos));
				}
			}

		}
	}
	else
	{
		std::cout << map->getStatusMessage() << std::endl;
	}

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

		//for (Platform& platform : platforms)
		//{
		//	for (Entity* entity : entities)
		//	{
		//		Collider entityCollider = entity->GetCollider();

		//		if (platform.GetCollider().CheckCollision(entityCollider, 1.0f, direction))
		//			entity->OnCollision(direction);

		//	}

		//}

		//std::cout << "x " << player->GetPosition().x << " y " << player->GetPosition().y << std::endl;

		view.setCenter(player->GetPosition());

		window.clear();
		for (Platform& platform : platforms)
			platform.Draw(window);

		for (Entity* entity : entities)
		{
			entity->Draw(window);
			entity->Update(deltaTime);
		}
		window.setView(view);

		window.display();
	}

	return 0;
}