#include <SFML/Graphics.hpp>
#include <iostream>
#include "tileson.hpp"
#include <Player.h>
#include <Platform.h>
#include <Collider.h>
#include <Slime.h>
#include <EnemiesManager.h>

static const float VIEW_HEIGHT = 720.0f;
static const float SLIME_SPAWN_TIMERMAX = 3.0f;

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
	std::vector<Animation*> playerAnimations;
	sf::Texture playerDefault;
	sf::Texture playerWalk;
	sf::Texture playerJump;
	sf::Texture playerAttack;

	playerDefault.loadFromFile("Art/PlayerDefault.png");
	playerWalk.loadFromFile("Art/PlayerWalk.png");
	playerAttack.loadFromFile("Art/PlayerAttack.png");

	playerAnimations.push_back(&Animation(&playerDefault, 7, 0.25f));
	playerAnimations.push_back(&Animation(&playerWalk, 12, 0.12f));
	playerAnimations.push_back(&Animation(&playerJump, 4, 0.2f));
	playerAnimations.push_back(&Animation(&playerAttack, 9, 0.035f));

	// load slime textures
	std::vector<Animation*> slimeAnimations;
	sf::Texture slimeDefault;
	sf::Texture slimeJump;
	sf::Texture slimeAir;
	sf::Texture slimeHit;

	slimeDefault.loadFromFile("Art/SlimeDefault.png");
	slimeJump.loadFromFile("Art/SlimeJump.png");
	slimeAir.loadFromFile("Art/SlimeInAir.png");
	slimeHit.loadFromFile("Art/SlimeHit.png");

	slimeAnimations.push_back(&Animation(&slimeDefault, 8, 0.05f, "Default"));
	slimeAnimations.push_back(&Animation(&slimeJump, 3, 0.2f, "Jump"));
	slimeAnimations.push_back(&Animation(&slimeAir, 1, 0.2f, "Air"));
	slimeAnimations.push_back(&Animation(&slimeHit, 6, 0.2f, "Hit"));

	sf::Sprite Ground;
	Ground.setTexture(groundtexture);

	Player* player = new Player(playerAnimations, 250.0f);
	Slime* slime = new Slime(slimeAnimations, sf::Vector2f(), &player->GetCollider().GetBody());
	slime->SetPosition(sf::Vector2f(100, 100));
	//Slime* slime2 = slime->Clone();
	//slime2->SetPosition(sf::Vector2f(300, 100));

	std::vector<Entity*> entities;

	
	entities.push_back(player);
	//entities.push_back(slime);
	//entities.push_back(slime2);

	std::vector<Platform> platforms;

	float deltaTime = 0.0f;
	sf::Clock clock;

#pragma region  Level gen
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
#pragma endregion

	EnemiesManager em = EnemiesManager(slime, &entities);

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

		window.clear();
		for (Platform& platform : platforms)
			platform.Draw(window);

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
