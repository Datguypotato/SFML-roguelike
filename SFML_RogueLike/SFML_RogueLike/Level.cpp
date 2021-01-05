#include "Level.h"

Level::Level(std::map<int, sf::Texture*>* tileSet, fs::path levelPath)
	:	doneLoading(false),
		startLoading(false)
{
	this->tileSet = tileSet;
	this->levelPath = levelPath;
}

Level::Level(std::map<int, sf::Texture*>* tileSet, fs::path levelPath, std::function<void()> Changelevel)
	:	Level::Level(tileSet, levelPath)
{
	this->Changelevel = Changelevel;
}

Level::~Level()
{
}

void Level::Load(Player* p, EnemiesManager* em)
{
	tson::Tileson t;
	map = t.parse(levelPath);
	doneLoading = false;

	if (map->getStatus() == tson::ParseStatus::OK)
	{
		for (auto& layer : map->getLayers())
		{

			if (layer.getType() == tson::LayerType::TileLayer)
			{
				// [id, obj]
				for (const auto& tileObject : layer.getTileObjects())
				{
					tson::TileObject obj = tileObject.second;
					int blockID = (int)obj.getTile()->get<int>("Order");

					if (blockID == 2)
					{
						std::cout << "ä";
					}

					sf::Vector2f Pos = sf::Vector2f(obj.getPosition().x, obj.getPosition().y);
					sf::Vector2f size = sf::Vector2f(obj.getTile()->getTileSize().x, obj.getTile()->getTileSize().y);

					switch (blockID)
					{
					case(0):
						floors.push_back(Ground(tileSet->operator[](blockID), size, Pos));
						break;
					case(1):
						walls.push_back(Wall(tileSet->operator[](blockID), size, Pos));
						break;
					case(2):
						doors.push_back(LevelSwitcher(tileSet->operator[](blockID), size, Pos));
						break;
					default:
						break;
					}
				}
			}
			else if (layer.getType() == tson::LayerType::ObjectGroup)
			{
				int index = 0;
				for (auto it = begin(layer.getObjects()); it != end(layer.getObjects()); ++it)
				{
					if (it->isPoint())
					{
						if (it->getName() == "PlayerSpawn")
						{
							p->SetPosition(sf::Vector2f(it->getPosition().x, it->getPosition().y));
							std::cout << "player start position = " << it->getPosition().x << " " << it->getPosition().y << std::endl;
						}
						else if (it->getName() == "SlimeSpawn")
						{
							em->AddEnemyData(EnemyType::Slime, it->get<float>("SpawnTime"), sf::Vector2f(it->getPosition().x, it->getPosition().y));
						}
					}
				}

			}

		}
	}
	else
	{
		std::cout << map->getStatusMessage() << std::endl;
	}

	doneLoading = true;
}

void Level::Unload()
{
	for (auto floor : floors)
		floor.~Ground();

	for (auto wall : walls)
		wall.~Wall();

	for (auto door : doors)
		door.~LevelSwitcher();
}

void Level::CheckCollision(Collider playerCollider)
{
	for (auto wall : walls)
		wall.GetCollider().CheckCollision(playerCollider, 1);
}

void Level::CheckTrigger(Collider playerCollider)
{
	for (auto door : doors)
		if (door.GetCollider().CheckTrigger(playerCollider) && Changelevel != nullptr)
		{
			Changelevel();
			startLoading = true;
		}
}


void Level::Draw(sf::RenderWindow& window)
{
	for (auto Floor : floors)
		Floor.Draw(window);

	for (auto wall : walls)
		wall.Draw(window);

	for (auto door : doors)
		door.Draw(window);
}