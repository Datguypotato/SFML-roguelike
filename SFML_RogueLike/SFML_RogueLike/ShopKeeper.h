#pragma once
#include "Interactable.h"
#include "InventorySlot.h"
#include "ItemBuilder.h"

class ShopKeeper :
    public Interactable
{
public:
    ShopKeeper(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);

    void Update(float deltaTime, sf::Vector2f mousePos);
    void Draw(sf::RenderWindow& window);

private:
    std::vector<InventorySlot*> buySlots;
    int amountSlot;

    bool isDrawing = false;
};

