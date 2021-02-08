#pragma once
#include "Ground.h"

class Interactable :
    public Ground
{
public:
    Interactable(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);
    ~Interactable();

    void CheckTrigger(Collider pColl);

    virtual void OnEnter() {}
    virtual void OnStay() {}
    virtual void OnExit() {}

protected:
    bool InTrigger;
    bool lastTimeIn;
};

