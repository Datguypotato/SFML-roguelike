#include "LootManager.h"

LootManager::LootManager()
	:	weaponb(new WeaponBuilder()),
		armourb(new ArmourBuilder()),
		legArmourb(new LegArmourBuilder())
{
}

void LootManager::Update(float deltaTime)
{
	for (Collectable* loot : Getloots())
	{
		loot->Update(deltaTime);
	}
}

void LootManager::CheckTrigger(Player* p)
{
	Collider pcoll = p->GetCollider();
	for (Collectable* loot : Getloots())
	{
		if (loot->GetCollider().CheckTrigger(pcoll) && loot->GetAliveStatus())
			p->CollectItem(loot);
	}
}

void LootManager::Draw(sf::RenderWindow& window)
{
	for (Collectable* loot : Getloots())
	{
		loot->Draw(window);
	}
}

Item* LootManager::GetRandomLoot()
{
	return nullptr;
}

std::vector<Collectable*> LootManager::Getloots()
{
	std::vector<Collectable*> temp = std::vector<Collectable*>();
	std::vector<Collectable*> weapon = weaponb->GetLoot();
	std::vector<Collectable*> armour = armourb->GetLoot();
	std::vector<Collectable*> legArmour = legArmourb->GetLoot();

	temp.insert(temp.end(), weapon.begin(), weapon.end());
	temp.insert(temp.end(), armour.begin(), armour.end());
	temp.insert(temp.end(), legArmour.begin(), legArmour.end());

	return temp;
}

