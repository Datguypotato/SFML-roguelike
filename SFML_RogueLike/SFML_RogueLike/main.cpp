#include <SFML/Graphics.hpp>
#include <iostream>
#include "tileson.hpp"

#include <EnemiesManager.h>
#include <Player.h>
#include <Slime.h>
#include <Ground.h>
#include <Collider.h>
#include <Button.h>

static const float VIEW_HEIGHT = 720.0f;
static const float SLIME_SPAWN_TIMERMAX = 3.0f;

void ButtonClicked();
void ResizeView(const sf::RenderWindow& window, sf::View& view);

void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
	float aspectRatio = float(window.getSize().x / float(window.getSize().y));

	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

void ButtonClicked()
{
	std::cout << "Button has been clicked\n";
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Super awesome game", sf::Style::Close | sf::Style::Resize);
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(1280.0f, 720.0f));

	sf::Font font;
	font.loadFromFile("Fonts/04B_30.TTF");
	sf::Text testingText;
	testingText = sf::Text("button", font, 10);
	testingText.setFillColor(sf::Color::Blue);

	Button button = Button(sf::Vector2f(200, 100), window.mapPixelToCoords(sf::Vector2i(0, 0)), std::function(ButtonClicked), testingText, &window);

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

	playerAnimations.push_back(new Animation(&playerDefault, 7, 0.25f, "Default"));
	playerAnimations.push_back(new Animation(&playerWalk, 12, 0.12f, "Walk"));
	playerAnimations.push_back(new Animation(&playerAttack, 9, 0.035f, "Attack"));

	Player* player = new Player(playerAnimations, 250.0f);

	std::vector<Entity*> entities;
	entities.push_back(player);
	std::vector<Ground> Floor;

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

					Floor.push_back(Ground(&groundtexture, groundSize, groundPos));
				}
			}

		}
	}
	else
	{
		std::cout << map->getStatusMessage() << std::endl;
	}
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
		//testingText.setPosition(window.mapPixelToCoords(sf::Vector2i(0,0)));
		button.SetPosition(window.mapPixelToCoords(sf::Vector2i(0, 0)));

		sf::Vector2f mousepos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
		if (button.CursorIsInBox(mousepos))
			button.OnClick();


		window.clear();
		for (Ground& platform : Floor)
			platform.Draw(window);

		for (Entity* entity : entities)
		{
			entity->Draw(window);
			entity->Update(deltaTime);
		}
		//window.draw(testingText);
		button.Draw(window);

		em.Update(deltaTime);
		window.setView(view);

		window.display();
	}

	return 0;
}
