#pragma once
#include "Shield.h"
class ShieldSword :
    public Shield
{
public:
    ShieldSword(sf::Texture* itemText, std::string name);

    int OnHit(Entity* entity) override;
};