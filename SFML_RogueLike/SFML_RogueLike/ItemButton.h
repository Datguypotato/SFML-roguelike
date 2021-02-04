#pragma once
#include "Button.h"
#include "Item.h"

class ItemButton :
    public Button
{
public:
    ItemButton(Item* i, sf::Vector2f pos, std::function<void(sf::RectangleShape box)> callBack, sf::Texture* texture);

    void OnClick(sf::Vector2f mousePos);

private:
    Item* item;
};

