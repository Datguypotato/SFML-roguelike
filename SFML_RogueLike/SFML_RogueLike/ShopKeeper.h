#pragma once
#include "Interactable.h"
#include "InventorySlot.h"
#include "ItemBuilder.h"

class ShopKeeper :
    public Interactable
{
public:
    ShopKeeper(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, Player* p);

    void Update(float deltaTime, sf::Vector2f mousePos, sf::Vector2f playerPos);
    void Draw(sf::RenderWindow& window);

private:
    Player* player;

    std::vector<InventorySlot*> buySlots;
    int amountSlot;

    sf::RectangleShape backgroundPanel;
    bool isDrawing = false;
};

