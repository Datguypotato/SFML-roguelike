#pragma once
#include "ThiefRobe.h"

class MagicRobe :
    public ThiefRobe
{
public:
    MagicRobe(sf::Texture* itemText, std::string name);

    MagicRobe* Clone() { return new MagicRobe(*this); }

    void OnRoll(Entity* player, sf::Vector2f dir) override;
    void SetRoll() override;

    int OnDamaged(int damage, Entity* e, sf::Vector2f playerPos) override;

    std::string GetItemStats() override;
};

