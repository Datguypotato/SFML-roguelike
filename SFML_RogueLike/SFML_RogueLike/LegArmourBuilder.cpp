#include "LegArmourBuilder.h"

LegArmourBuilder::LegArmourBuilder()
{
}

Collectable* LegArmourBuilder::BuildLegArmour(int ID, sf::Vector2f position)
{
    switch (ID)
    {
    case 0:
        return BuildRedPants(position);
        break;
    case 1:
        return BuildGreenPants(position);
        break;
    case 2:
        return BuildBluePants(position);
    default:
        std::cout << "ID: " << ID << " not found\n";
        return nullptr;
        break;
    }
}

Collectable* LegArmourBuilder::BuildRedPants(sf::Vector2f position)
{
    sf::Texture* text = new sf::Texture();
    text->loadFromFile("Art/Item/RedPants.png");
    std::vector<Animation*> animations = std::vector<Animation*>();
    animations.push_back(new Animation(text, 1, 0.0f, "Default"));
    
    Collectable* col = new Collectable(animations, position, new RedPants(text, "Red pants", BuildUpgradeRedPants()));
    loot.push_back(col);
    return col;
}

Item* LegArmourBuilder::BuildUpgradeRedPants()
{
    return new RedPantsSpikes(Loadtexture("RedPantsSpikes"), "RedPantsSpikes");
}

Collectable* LegArmourBuilder::BuildGreenPants(sf::Vector2f position)
{
    sf::Texture* text = new sf::Texture();
    text->loadFromFile("Art/Item/GreenPants.png");
    std::vector<Animation*> animations = std::vector<Animation*>();
    animations.push_back(new Animation(text, 1, 0.0f, "Default"));

    Collectable* col = new Collectable(animations, position, new GreenPants(text, "Green pants", BuildUpgradeGreenPants()));
    loot.push_back(col);
    return col;
}

Item* LegArmourBuilder::BuildUpgradeGreenPants()
{
    return new GreenPantsUpgrade(Loadtexture("GreenPantsSpikes"), "GreenPantsSpikes");;
}

Collectable* LegArmourBuilder::BuildBluePants(sf::Vector2f position)
{
    sf::Texture* text = new sf::Texture();
    text->loadFromFile("Art/Item/BluePants.png");
    std::vector<Animation*> animations = std::vector<Animation*>();
    animations.push_back(new Animation(text, 1, 0.0f, "Default"));

    Collectable* col = new Collectable(animations, position, new BluePants(text, "Blue pants", BuildUpgradeBluePants()));
    loot.push_back(col);
    return col;
}

Item* LegArmourBuilder::BuildUpgradeBluePants()
{
    return new BluePantsUpgrade(Loadtexture("BluePantsSpikes"), "BluePantsSpikes");;
}

sf::Texture* LegArmourBuilder::Loadtexture(std::string path)
{
    sf::Texture* text = new sf::Texture();
    text->loadFromFile("Art/Item/" + path + ".png");
    return text;
}
