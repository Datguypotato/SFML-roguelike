#pragma once
#include "RedShirt.h"

class RedSpikes :
    public RedShirt
{
public:
    RedSpikes(sf::Texture* itemText, std::string name);

    int OnDamaged(int damage, Entity* e, sf::Vector2f playerPos) override;
};

