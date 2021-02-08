#include "Level.h"

Level::Level(std::vector<sf::Texture*> tileSet, fs::path levelPath)
	:	doneLoading(false),
		startLoading(false)
{
	this->tileSet = tileSet;
	this->levelPath = levelPath;
	textSigns = CreateTextSigns();
}

Level::Level(std::vector<sf::Texture*> tileSet, fs::path levelPath, std::function<void()> Changelevel)
	:	Level::Level(tileSet, levelPath)
{
	this->Changelevel = Changelevel;
}

Level::~Level()
{
}

void Level::Load(Player* p, EnemiesManager* em, LootManager* lm)
{
	p->GetSynergyManager()->OnStartLevel(p);
	tson::Tileson t;
	map = t.parse(levelPath);
	doneLoading = false;
	if (map->getStatus() == tson::ParseStatus::OK)
	{
		int multiplier = 4;
		for (auto& layer : map->getLayers())
		{
			if (layer.getType() == tson::LayerType::TileLayer)
			{
				// [id, obj]
				for (const auto& tileObject : layer.getTileData())
				{
					tson::Tile obj = *tileObject.second;
					int blockID = obj.getId() - 1;

					sf::Vector2f pos = sf::Vector2f(obj.getPosition(tileObject.first).x * multiplier, obj.getPosition(tileObject.first).y * multiplier);//offset since the sprite are too small
					sf::Vector2f size = sf::Vector2f(32.0f * multiplier, 32.0f * multiplier);
					int blockType = obj.get<int>("BlockType");
					std::string interactableText;

					switch (blockType)
					{
					case 0:
						floors.push_back(Ground(tileSet[blockID], size, pos));
						break;
					case 1:
						walls.push_back(Wall(tileSet[blockID], size, pos));
						break;
					case 2:
						doors.push_back(LevelSwitcher(tileSet[blockID], size, pos));
						break;
					case 3:
						interactableText = textSigns[0];
						textSigns.erase(textSigns.begin());
						interactables.push_back(new LevelSign(tileSet[blockID], size, pos, interactableText));
						break;
					case 4:
						invisibleWalls.push_back(Wall(nullptr, size, pos));
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
						std::string name = it->getName();
						sf::Vector2f tempPos = sf::Vector2f(it->getPosition().x * multiplier, it->getPosition().y * multiplier); //offset since the sprite are too small
						sf::Vector2f spawnPos = tempPos;

						if (it->getName() == "PlayerSpawn")
						{
							p->SetPosition(spawnPos);
						}
						else if (it->getName() == "SpawnWeapon")
						{
							lm->GetWeaponb()->BuildWeapon(it->get<int>("id"), spawnPos);
						}
						else if (it->getName() == "SpawnArmour")
						{
							lm->GetArmourb()->BuildArmour(it->get<int>("id"), spawnPos);
						}
						else if (it->getName() == "SpawnLegArmour")
						{
							lm->GetLegArmourb()->BuildLegArmour(it->get<int>("id"), spawnPos);
						}
						else if (it->getName() == "SpawnShopkeeper")
						{
							sf::Texture* texture = new sf::Texture();
							texture->loadFromFile("Art/Evilmerchant.png");

							shopkeeper = new ShopKeeper(texture, sf::Vector2f(80, 80), spawnPos);
						}
						else
						{
							EnemyType type = (EnemyType)it->get<int>("EnemyType");
							float spawnTime = it->get<float>("SpawnTime");
							em->AddEnemyData(type, spawnTime, spawnPos);
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

void Level::CheckTrigger(Collider playerCollider, EnemiesManager em)
{
	if (em.IsFinished())
	{
		for (auto door : doors)
		{
			if (door.GetCollider().CheckTrigger(playerCollider) && Changelevel != nullptr)
			{
				Changelevel();
				startLoading = true;
			}
		}
	}
	else
	{
		for (auto door : doors)
			door.GetCollider().CheckCollision(playerCollider, 1);

		for (auto iWalls : invisibleWalls)
			iWalls.GetCollider().CheckCollision(playerCollider, 1);
	}

	for (auto interact : interactables)
	{
		interact->CheckTrigger(playerCollider);
	}

	shopkeeper->CheckTrigger(playerCollider);
}

std::vector<std::string> Level::CreateTextSigns()
{
	std::vector<std::string> texts = std::vector<std::string>();

	texts.push_back("Items can be picked by walking over it\nItems give special bonuses");
	texts.push_back("Press z to attack \n(remember that you have a\n small cooldown when attacking)");
	texts.push_back("You can move around\n With you arrows keys");

	return texts;
}


void Level::Draw(sf::RenderWindow& window)
{
	for (auto Floor : floors)
		Floor.Draw(window);

	for (auto wall : walls)
		wall.Draw(window);

	for (auto door : doors)
		door.Draw(window);

	shopkeeper->Draw(window);
}

void Level::LateDraw(sf::RenderWindow& window)
{
	for (auto interact : interactables)
		interact->Draw(window);
}
