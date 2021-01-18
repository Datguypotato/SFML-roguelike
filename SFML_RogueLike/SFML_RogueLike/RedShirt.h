#pragma once
#include "ArmourItem.h"
class RedShirt :
    public ArmourItem
{
public:
    RedShirt(sf::Texture* itemText, std::string name);
    RedShirt(sf::Texture* itemText, std::string name, Item* upgrade);

    RedShirt* Clone() { return new RedShirt(*this); }
    void Update(float deltaTime);

    int OnDamaged(int damage, Entity* e, sf::Vector2f playerPos) override;

protected:
    float timer;
    float maxTimer;
};