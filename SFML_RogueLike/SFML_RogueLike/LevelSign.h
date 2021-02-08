#pragma once
#include "Interactable.h"

class LevelSign :
    public Interactable
{
public:
    LevelSign(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, std::string text);

    void Draw(sf::RenderWindow& window);

private:
    sf::Text* text;
};

