#include "LevelManager.h"

LevelManager::LevelManager(std::map<int, sf::Texture*> tileset, std::vector<fs::path> paths, std::function<void()> Changelevel, Player* p, EnemiesManager* em)
	:	activeLevelIndex(0),
		lerpTime(0)
{
	this->p = p;
	levels = std::vector<Level*>();
	for (auto path : paths)
	{
		levels.push_back(new Level(tileset, path, Changelevel));
	}

	//transitionScale = sf::Vector2f(320.0f, 180.0f);
	//transitionScreen.setSize(transitionScale);
	//transitionScreen.setOrigin(transitionScreen.getSize() / 2.0f);
	//transitionScreen.setFillColor(sf::Color::Black);
	//transitionScreen.setOutlineColor(sf::Color::White);
}

LevelManager::~LevelManager()
{
}

void LevelManager::Update(float deltaTime)
{
	//TODO enlarge the size of transition screen till done loading
	//if (levels[activeLevelIndex]->isStartLoading())
	//{
	//	lerpTime += deltaTime;
	//	transitionScreen.setScale(Lerp(transitionScreen.getScale().x, 1920.0f, lerpTime)
	//							, Lerp(transitionScreen.getScale().y, 1080.0f, lerpTime));
	//}
}

float LevelManager::Lerp(float a, float b, float t)
{
	return a * (1 - t) + b * t;
}

void LevelManager::NextLevel()
{
	LevelManager::SwitchLevel(activeLevelIndex + 1);
}

void LevelManager::SwitchLevel(int index)
{
	// TODO set transition screen back to normal
	levels[activeLevelIndex]->Unload();
	activeLevelIndex++;
	levels[index]->Load(p);
}

void LevelManager::CenterRectangleShape(sf::Vector2f newPos)
{
	//transitionScreen.setPosition(newPos);
}

Level* LevelManager::GetCurrentLevel()
{
	return levels[activeLevelIndex];
}

void LevelManager::Draw(sf::RenderWindow& window)
{
	//if (levels[activeLevelIndex]->isStartLoading())
		//window.draw(transitionScreen);
}

