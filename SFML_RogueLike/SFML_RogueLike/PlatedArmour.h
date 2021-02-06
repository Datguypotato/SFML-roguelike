#pragma once
#include "KevlarVest.h"
class PlatedArmour :
    public KevlarVest
{
public:
    PlatedArmour(sf::Texture* itemText, std::string name);
    PlatedArmour* Clone() override { return new PlatedArmour(*this); }

    void OnExplodeShield(sf::Vector2f playerPos) override;
    void CheckCollision(std::vector<Entity*> entities) override;

    std::string GetItemStats() override;
private:
    float Distance(sf::Vector2f a, sf::Vector2f b);

    sf::RectangleShape explosionBox;
    bool isExploded = false;
    float range = 250.0f;
    int explosionDamage = 10;
};

