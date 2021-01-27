#include "WeaponBuilder.h"

WeaponBuilder::WeaponBuilder()
	:	loots(std::vector<Collectable*>())
{
}

/// <summary>
/// 0 = Knife
/// 1 = FanSword
/// 2 = Shield
/// </summary>
/// <param name="id"></param>
/// <param name="position"></param>
/// <returns></returns>
void WeaponBuilder::BuildWeapon(int id, sf::Vector2f position)
{
	Collectable* c;

	switch (id)
	{
	case 0:
		BuildKnife(position);
		break;
	case 1:
		BuildFanSword(position);
		break;
	case 2:
		BuildShield(position);
		break;
	default:
		std::cout << "Error Weapon ID: " << id << " not found\n";
		break;
	}
}

Collectable* WeaponBuilder::BuildKnife(sf::Vector2f pos)
{
	sf::Texture* texture = LoadTexture("Knife");

	Item* ie = new Knife(texture, "Lovely Knife", UpgradeKnife());
	std::vector<Animation*> temp;
	temp.push_back(new Animation(texture, 1, 1, "Default"));

	Collectable* col = new Collectable(temp, pos, ie);
	loots.push_back(col);

	return col;
}

Collectable* WeaponBuilder::BuildUpgradeKnife(sf::Vector2f pos)
{
	sf::Texture* texture = LoadTexture("BloodKnife");

	std::vector<Animation*> temp;
	temp.push_back(new Animation(texture, 1, 1, "Default"));

	Collectable* col = new Collectable(temp, pos, UpgradeKnife());
	loots.push_back(col);

	return col;
}

Collectable* WeaponBuilder::BuildFanSword(sf::Vector2f pos)
{
	sf::Texture* texture = LoadTexture("WindKnife");
	Item* ie = new FanSword(texture, "WindKnife", UpgradeFanSword());

	std::vector<Animation*> temp;
	temp.push_back(new Animation(texture, 1, 1, "Default"));

	Collectable* col = new Collectable(temp, pos, ie);
	loots.push_back(col);

	return col;
}

Item* WeaponBuilder::UpgradeFanSword()
{
	Item* ie = new WindSlasher(LoadTexture("WindSlasher"), "Windslasher");

	return ie;
}

Collectable* WeaponBuilder::BuildShield(sf::Vector2f pos)
{
	sf::Texture* texture = LoadTexture("Shield");
	Item* ie = new Shield(texture, "Shield", UpgradeShield());

	std::vector<Animation*> temp;
	temp.push_back(new Animation(texture, 1, 1, "Default"));

	Collectable* col = new Collectable(temp, pos, ie);
	loots.push_back(col);

	return col;
}

Item* WeaponBuilder::UpgradeShield()
{
	Item* ie = new ShieldSword(LoadTexture("ShieldSword"), "ShieldSword");

	return ie;
}

Item* WeaponBuilder::UpgradeKnife()
{
	sf::Texture* texture = LoadTexture("BloodKnife");
	Item* ie = new BloodKnife(texture, "Lovely Bloody Knife");

	return ie;
}

sf::Texture* WeaponBuilder::LoadTexture(std::string path)
{
	sf::Texture* texture = new sf::Texture();
	texture->loadFromFile("Art/Item/" + path + ".png");
	return texture;
}
