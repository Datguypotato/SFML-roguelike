#pragma once
#include "BluePants.h"
class BluePantsUpgrade :
    public BluePants
{
public:
    BluePantsUpgrade(sf::Texture* itemText, std::string name);

    std::string GetItemStats() override;
};

