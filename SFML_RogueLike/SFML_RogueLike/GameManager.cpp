#include "GameManager.h"

GameManager::GameManager(sf::View view, Player p, LevelManager lm)
	:	levelmanager(lm),
		player(p),
		totalTime(0)
{
	this->view = view;
	this->window = new sf::RenderWindow(sf::VideoMode(1280, 720), "Super awesome game", sf::Style::Close | sf::Style::Resize);
}

GameManager::~GameManager()
{
}

void GameManager::ResizeView(const sf::RenderWindow& window, sf::View& view)
{
	float aspectRatio = float(window.getSize().x / float(window.getSize().y));

	view.setSize(720 * aspectRatio, 720);
}

void GameManager::Update(float deltaTime)
{
	totalTime += deltaTime;
	player.Update(deltaTime);

	for (Enemy enemy : enemies)
	{
		enemy.Update(deltaTime);
	}

}

void GameManager::CheckCollision()
{
	Collider pcoll = player.GetCollider();
	for (Enemy enemy : enemies)
	{
		if (enemy.GetCollider().CheckCollision(pcoll, 0.8f))
			player.OnHit(1);
	}

	levelmanager.GetCurrentLevel()->CheckCollision(pcoll);
	levelmanager.GetCurrentLevel()->CheckTrigger(pcoll);
}

void GameManager::Draw()
{
	window->clear();

	levelmanager.GetCurrentLevel()->Draw(*window);
	player.Draw(*window);

	for (Enemy enemy : enemies)
	{
		enemy.Draw(*window);
	}

	view.setCenter(player.GetPosition());
	window->setView(view);
	window->display();
}
