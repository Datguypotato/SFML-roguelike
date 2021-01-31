#pragma once
#include "LegArmourItem.h"
class BluePants :
    public LegArmourItem
{
public:
    BluePants(sf::Texture* itemText, std::string name);
    BluePants(sf::Texture* itemText, std::string name, Item* upgrade);

    void OnLevelEnd(Entity* player) override;

protected:
    int addMaxHealthValue = 10;
    int healValue = 0;
};

