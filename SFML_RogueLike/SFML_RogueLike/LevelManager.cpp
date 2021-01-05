#include "LevelManager.h"

LevelManager::LevelManager(std::function<void()> Changelevel, Player* p)
	:	activeLevelIndex(0),
		lerpTime(0)
{
	this->p = p;
	levels = std::vector<Level*>();

	std::vector<fs::path> paths = std::vector<fs::path>();
	paths.push_back("../SFML_RogueLike/Art/World/Test.json");
	paths.push_back("../SFML_RogueLike/Art/World/Test2.json");

	levels = std::vector<Level*>();
	for (auto path : paths)
	{
		levels.push_back(new Level(CreateTiles(), path, Changelevel));
	}
}

LevelManager::~LevelManager()
{
}

float LevelManager::Lerp(float a, float b, float t)
{
	return a * (1 - t) + b * t;
}

void LevelManager::NextLevel(EnemiesManager* em)
{
	LevelManager::SwitchLevel(activeLevelIndex + 1, em);
}

void LevelManager::SwitchLevel(int index, EnemiesManager* em)
{
	// TODO set transition screen back to normal
	levels[activeLevelIndex]->Unload();
	activeLevelIndex++;
	levels[index]->Load(p, em);
}

void LevelManager::CenterRectangleShape(sf::Vector2f newPos)
{
	//transitionScreen.setPosition(newPos);
}

Level* LevelManager::GetCurrentLevel()
{
	return levels[activeLevelIndex];
}

std::map<int, sf::Texture*>* LevelManager::CreateTiles()
{
	std::map<int, sf::Texture*>* tileSet = new std::map<int, sf::Texture*>();
	sf::Texture* groundtexture = new sf::Texture();
	sf::Texture* oldGround = new sf::Texture();
	sf::Texture* door = new sf::Texture();

	groundtexture->loadFromFile("Art/World/GrassTopDown.png");
	oldGround->loadFromFile("Art/World/GrassGround.png");
	door->loadFromFile("Art/World/door.png");
	tileSet->insert(std::pair(0, groundtexture));
	tileSet->insert(std::pair(1, oldGround));
	tileSet->insert(std::pair(2, door));

	return tileSet;
}