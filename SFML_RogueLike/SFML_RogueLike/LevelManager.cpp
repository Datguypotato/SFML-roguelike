#include "LevelManager.h"

LevelManager::LevelManager(std::function<void()> Changelevel, Player* p)
	:	activeLevelIndex(0),
		lerpTime(0)
{
	this->p = p;
	levels = std::vector<Level*>();

	std::vector<fs::path> paths = std::vector<fs::path>();
	paths.push_back("../SFML_RogueLike/Art/World/Levels/Tutorial.json");
	paths.push_back("../SFML_RogueLike/Art/World/Test2.json");

	levels = std::vector<Level*>();
	for (fs::path path : paths)
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

void LevelManager::NextLevel(EnemiesManager* em, LootManager* lm)
{
	LevelManager::SwitchLevel(activeLevelIndex + 1, em, lm);
}

void LevelManager::SwitchLevel(int index, EnemiesManager* em, LootManager* lm)
{
	// TODO set transition screen back to normal
	levels[activeLevelIndex]->Unload();
	activeLevelIndex++;
	levels[index]->Load(p, em, lm);
}

void LevelManager::CenterRectangleShape(sf::Vector2f newPos)
{
	//transitionScreen.setPosition(newPos);
}

Level* LevelManager::GetCurrentLevel()
{
	return levels[activeLevelIndex];
}

std::vector<sf::Texture*> LevelManager::CreateTiles()
{
	std::vector<sf::Texture*> tileSet = std::vector<sf::Texture*>();
	sf::Texture* groundtexture = new sf::Texture();
	sf::Texture* oldGround = new sf::Texture();
	sf::Texture* door = new sf::Texture();

	std::string path = "Art/World/Tiles Generic";

	for (const auto& entry : fs::directory_iterator(path))
	{
		sf::Texture* texture = new sf::Texture();
		texture->loadFromFile(entry.path().u8string());
		tileSet.push_back(texture);
	}

	return tileSet;
}