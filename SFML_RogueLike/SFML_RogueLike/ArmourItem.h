#pragma once
#include <vector>

#include "Entity.h"
#include "Item.h"

class ArmourItem :
    public Item
{
public:
    ArmourItem(sf::Texture* itemText, std::string name);
    ArmourItem(sf::Texture* itemText, std::string name, Item* upgrade);

    virtual ArmourItem* Clone() { return new ArmourItem(*this); }


    virtual int OnDamaged(int damage, Entity* e, sf::Vector2f playerPos) { return damage; }
    virtual void OnRoll(Entity* player, sf::Vector2f dir) {}
    virtual void SetRoll() {}

    bool GetProtectStatus() { return isProtected; }
    bool GetCanRollStatus() { return CanRoll; }
    bool GetIsRollStatus() { return CanRoll; }

    virtual int GetShield() { return 0; }
    virtual void GainShield(int amount){}
    virtual void SetShield(int amount){}
    virtual void OnExplodeShield(sf::Vector2f playerPos) {}
    virtual void CheckCollision(std::vector<Entity*> entities) {}

protected:
    bool isProtected = false;

    bool CanRoll = false;
    bool IsRolling = false;
};
