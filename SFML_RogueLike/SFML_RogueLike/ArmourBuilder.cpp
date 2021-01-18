#include "ArmourBuilder.h"

ArmourBuilder::ArmourBuilder()
	:	loots(std::vector<Collectable*>())
{

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
