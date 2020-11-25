#include "Level.h"

Level::Level(std::map<int, sf::Texture*> tileSet, fs::path levelPath)
{
	this->tileSet = tileSet;
	this->levelPath = levelPath;
}

Level::~Level()
{
}

void Level::Load()
{
	tson::Tileson t;
	map = t.parse(levelPath);

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
					sf::Vector2f Pos = sf::Vector2f(obj.getPosition().x, obj.getPosition().y);
					sf::Vector2f size = sf::Vector2f(obj.getTile()->getTileSize().x, obj.getTile()->getTileSize().y);

					int blockID = tileObject.second.getTile()->getId() - 1;		// so that it start counting at 0 instead of 1

					if (blockID == 1)
						walls.push_back(Wall(tileSet[blockID], size, Pos));
					else if (blockID == 2)
						doors.push_back(LevelSwitcher(tileSet[blockID], size, Pos));
					else
						floor.push_back(Ground(tileSet[blockID], size, Pos));

				}
			}

		}
	}
	else
	{
		std::cout << map->getStatusMessage() << std::endl;
	}
}

void Level::CheckCollision(Collider playerCollider)
{
	for (auto wall : walls)
		wall.GetCollider().CheckCollision(playerCollider, 1);
}

void Level::CheckTrigger(Collider playerCollider)
{
	for (auto door : doors)
		if (door.GetCollider().CheckTrigger(playerCollider))
			std::cout << "Player in door\n";
}


void Level::Draw(sf::RenderWindow& window)
{
	for (auto Floor : floor)
		Floor.Draw(window);

	for (auto wall : walls)
		wall.Draw(window);

	for (auto door : doors)
		door.Draw(window);
}