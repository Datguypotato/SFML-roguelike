#include "LevelManager.h"

LevelManager::LevelManager(std::function<void()> Changelevel, Player* p, EnemiesManager* e)
	:	activeLevelIndex(0),
		lerpTime(0),
		itemBuilder(new ItemBuilder())
{
	this->player = p;
	em = e;
	levels = std::vector<Level*>();

	std::vector<fs::path> paths = std::vector<fs::path>();
	paths.push_back("../SFML_RogueLike/Art/World/Levels/Dev.json");
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

void LevelManager::NextLevel(LootManager* lm)
{
	LevelManager::SwitchLevel(activeLevelIndex + 1, em, lm);
}

void LevelManager::SwitchLevel(int index, EnemiesManager* em, LootManager* lm)
{
	SetEndButtons();
	levels[activeLevelIndex]->Unload();
	player->GetSynergyManager()->OnEndLevel();
	activeLevelIndex++;
	levels[index]->Load(player, em, lm);
	chooseItem = false;
}

void LevelManager::CenterRectangleShape(sf::Vector2f newPos)
{
	//transitionScreen.setPosition(newPos);
}

void LevelManager::UpdateButtons(sf::Vector2f mousePos)
{
	if (em->IsFinished())
	{
		if (!buttonBuilt)
		{
			SetEndButtons();
			buttonBuilt = true;
		}
	}

	for (ItemButton* button : buttons)
	{
		button->CanUpdate(*player->GetBody());
		button->OnClick(mousePos);

		if (chooseItem)
			break;
	}
}

void LevelManager::DrawButtons(sf::RenderWindow& window)
{
	for (ItemButton* button : buttons)
	{
		button->Draw(window);
	}
}

void LevelManager::SetEndButtons()
{
	// TODO: finsih set up
	buttons.clear();
	buttons.push_back(BuildItemButton(sf::Vector2f(400, 0)));
	buttons.push_back(BuildItemButton(sf::Vector2f(0, 0)));
	buttons.push_back(BuildItemButton(sf::Vector2f(-400, 0)));
}

void LevelManager::EndButtonOnClick()
{
	for (ItemButton* button : buttons)
	{
		delete button;
		button = nullptr;
	}
	buttons.clear();
	chooseItem = true;
}

Level* LevelManager::GetCurrentLevel()
{
	return levels[activeLevelIndex];
}

ItemButton* LevelManager::BuildItemButton(sf::Vector2f position)
{
	sf::Texture* text = new sf::Texture();
	text->loadFromFile("Art/UI/ChooseItemBox.png");

	return new ItemButton(itemBuilder->BuildRandom(), position, std::bind(&LevelManager::EndButtonOnClick, this), text, player);
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