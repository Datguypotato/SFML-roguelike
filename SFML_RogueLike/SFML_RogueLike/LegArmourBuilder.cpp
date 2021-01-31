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
        break;
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
    
    Collectable* col = new Collectable(animations, position, new RedPants(text, "Red pants", BuildUpgradePants()));
    loot.push_back(col);
    return col;
}

Item* LegArmourBuilder::BuildUpgradePants()
{
    return new RedPantsSpikes(Loadtexture("RedPantsSpikes"), "RedPantsSpikes");
}

Collectable* LegArmourBuilder::BuildGreenPants(sf::Vector2f position)
{
    sf::Texture* text = new sf::Texture();
    text->loadFromFile("Art/Item/RedPants.png");
    std::vector<Animation*> animations = std::vector<Animation*>();
    animations.push_back(new Animation(text, 1, 0.0f, "Default"));
    return nullptr;
}

sf::Texture* LegArmourBuilder::Loadtexture(std::string path)
{
    sf::Texture* text = new sf::Texture();
    text->loadFromFile("Art/Item/" + path + ".png");
    return text;
}
