#include "ArmourBuilder.h"

ArmourBuilder::ArmourBuilder()
	:	loots(std::vector<Collectable*>())
{

}

Item* ArmourBuilder::BuildRandom()
{
	int random = rand() % 3;

	switch (random)
	{
	case 0:
		return new RedShirt(LoadTexture("RedShirt"), "RedShirt", BuildRedShirtUpgrade());
		break;
	case 1:
		return new ThiefRobe(LoadTexture("ThiefRobe"), "ThiefRobe", BuildUpgradeThiefRobe());
		break;
	case 2:
		return new KevlarVest(LoadTexture("KevlarVest"), "KevlarVest", BuildUpgradeKevelarVest());
	default:
		std::cout << "Error unexpected random number\n";
		return nullptr;
		break;
	}
}

/// <summary>
/// 0 = KevlarVest
/// 1 = RedShirt
/// 2 = ThiefRobe
/// </summary>
/// <param name="id"></param>
/// <param name="position"></param>
/// <returns></returns>
Collectable* ArmourBuilder::BuildArmour(int id, sf::Vector2f position)
{
	switch (id)
	{
	case 0:
		return BuildKevlarVest(position);
		break;
	case 1:
		return BuildRedShirt(position);
		break;
	case 2:
		return BuildThiefRobe(position);
		break;
	default:
		std::cout << "Error armour ID: " << id << " not found\n";
		return nullptr;
		break;
	}

	return nullptr;
}

Collectable* ArmourBuilder::BuildRedShirt(sf::Vector2f pos)
{
	sf::Texture* texture = LoadTexture("RedShirt");
	RedShirt* ie = new RedShirt(texture, "RedShirt", BuildRedShirtUpgrade());
	std::vector<Animation*> temp;
	temp.push_back(new Animation(texture, 1, 1, "Default"));
	Collectable* c = new Collectable(temp, pos, ie);
	loots.push_back(c);

    return c;
}

Item* ArmourBuilder::BuildRedShirtUpgrade()
{
	return new RedSpikes(LoadTexture("RedSpike"), "RedSpike");
}

Collectable* ArmourBuilder::BuildThiefRobe(sf::Vector2f pos)
{
	sf::Texture* texture = LoadTexture("ThiefRobe");
	ThiefRobe* ie = new ThiefRobe(texture, "ThiefRobe", BuildUpgradeThiefRobe());
	std::vector<Animation*> temp;
	temp.push_back(new Animation(texture, 1, 1, "Default"));
	Collectable* c = new Collectable(temp, pos, ie);
	loots.push_back(c);
	return c;
}

Item* ArmourBuilder::BuildUpgradeThiefRobe()
{
	return new MagicRobe(LoadTexture("WizardRobe"), "WizardRobe");
}

Collectable* ArmourBuilder::BuildKevlarVest(sf::Vector2f pos)
{
	sf::Texture* texture = LoadTexture("KevlarVest");
	KevlarVest* ie = new KevlarVest(texture, "KevlarVest", BuildUpgradeKevelarVest());
	std::vector<Animation*> temp;
	temp.push_back(new Animation(texture, 1, 1, "Default"));
	Collectable* c = new Collectable(temp, pos, ie);
	loots.push_back(c);
	return c;
}

Item* ArmourBuilder::BuildUpgradeKevelarVest()
{
	return new PlatedArmour(LoadTexture("PlatedArmour"), "Plated Armour");
}

sf::Texture* ArmourBuilder::LoadTexture(std::string path)
{
	sf::Texture* texture = new sf::Texture();
	texture->loadFromFile("Art/Item/" + path + ".png");
	return texture;
}
