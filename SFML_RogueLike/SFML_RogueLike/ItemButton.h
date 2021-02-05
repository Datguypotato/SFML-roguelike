#pragma once
#include "Button.h"
#include "Item.h"
#include "Player.h"

class ItemButton :
    public Button
{
public:
    ItemButton(Item* i, sf::Vector2f pos, std::function<void(sf::RectangleShape box)> callBack, sf::Texture* texture, Player* p);

    void ClickAction() override;
    void Update(sf::RectangleShape player) override;

    void Draw(sf::RenderWindow& window);

private:
    Item* item;
    sf::Text* text;
    Player* player;
};

