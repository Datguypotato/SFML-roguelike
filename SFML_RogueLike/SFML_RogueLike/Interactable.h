#pragma once
#include "Ground.h"
class Interactable :
    public Ground
{
public:
    Interactable(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, std::string signText);
    ~Interactable();

    void CheckTrigger(Collider pColl);
    void Draw(sf::RenderWindow& window);

private:
    sf::Text* text;
    bool InTrigger;
};

