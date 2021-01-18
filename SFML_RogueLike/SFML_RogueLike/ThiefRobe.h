#pragma once
#include "ArmourItem.h"
class ThiefRobe :
    public ArmourItem
{
public:
    ThiefRobe(sf::Texture* itemText, std::string name);
    ThiefRobe(sf::Texture* itemText, std::string name, Item* upgrade);

    ThiefRobe* Clone() { return new ThiefRobe(*this); }

    void Update(float deltaTime) override;
    void OnRoll(Entity* player, sf::Vector2f dir) override;
    void SetRoll() override;

protected:
    float rollPower = 0.5f;
    float rollTimer = 3;
    float rollTimerMax = rollTimer;

    float rollingTimer = 0.25f;
    float rollingTimerMax = rollingTimer;
};