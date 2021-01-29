#pragma once
#include <iostream>

#include "UIComponent.h"
#include "Item.h"

// TODO: 

class InventorySlot : public UIComponent
{
public:
	InventorySlot();
	InventorySlot(SlotRegion* sr);
	InventorySlot(Item* it);

	void Update(sf::Vector2f mousePos);

	void Draw(sf::RenderWindow& window);
	void DrawDescp(sf::RenderWindow& window);

	void Deleteitem();
	Item* GetItem() { return item; }
	void SetItem(Item* i);
	Item* GrabItem();
	Item* GrabItem(Item* i);

	bool isSlotEmpty() { return (isEmpty); }

	std::string GetItemDescription();
	SlotRegion GetSlotRegion() { return *slotRegion; }
private:
	bool isEmpty;
	bool cursorInBox;
	sf::Texture* emptySlotTexture;
	sf::Text* itemDescriptionText;
	Item* item;
	SlotRegion* slotRegion;
};

