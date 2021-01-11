#include "LootManager.h"

LootManager::LootManager()
	: loots(std::vector<Collectable*>())
{
}

void LootManager::Update(float deltaTime)
{
	for (Collectable* loot : loots)
	{
		loot->Update(deltaTime);
	}
}

void LootManager::CheckTrigger(Player* p)
{
	Collider pcoll = p->GetCollider();
	for (Collectable* loot : loots)
	{
		if (loot->GetCollider().CheckTrigger(pcoll) && loot->GetAliveStatus())
			p->CollectItem(loot);
	}
}

void LootManager::Draw(sf::RenderWindow& window)
{
	for (Collectable* loot : loots)
	{
		loot->Draw(window);
	}
}

Item* LootManager::GetRandomLoot()
{
	return nullptr;
}

Collectable* LootManager::BuildKnife(sf::Vector2f pos)
{
	sf::Texture* texture = new sf::Texture();
	texture->loadFromFile("Art/UI/Knife.png");

	Item* ie = new Knife(texture, "Lovely Knife", new SlotRegion(SlotRegion::Weapon), UpgradeKnife());
	std::vector<Animation*> temp;
	temp.push_back(new Animation(texture, 1, 1, "Default"));

	Collectable* col = new Collectable(temp, pos, ie);
	loots.push_back(col);

	return col;
}

Collectable* LootManager::BuildUpgradeKnife(sf::Vector2f pos)
{
	sf::Texture* texture = new sf::Texture();
	texture->loadFromFile("Art/UI/BloodKnife.png");

	std::vector<Animation*> temp;
	temp.push_back(new Animation(texture, 1, 1, "Default"));

	Collectable* col = new Collectable(temp, pos, UpgradeKnife());
	loots.push_back(col);

	return col;
}

Item* LootManager::UpgradeKnife()
{
	sf::Texture* texture = new sf::Texture();
	texture->loadFromFile("Art/UI/BloodKnife.png");

	Item* ie = new BloodKnife(texture, "Lovely Bloody Knife", new SlotRegion(SlotRegion::Weapon));

	return ie;
}