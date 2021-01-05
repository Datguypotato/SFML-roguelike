#pragma once
#include "UIComponent.h"
#include "Item.h"

// TODO: inherit from button instead?

class InventorySlot : public UIComponent
{
public:
	InventorySlot();
	InventorySlot(SlotRegion* sr);
	InventorySlot(Item* it);

	void Update(sf::RectangleShape player) override;

	void Draw(sf::RenderWindow& window);

	Item* GetItem() { return item; }
	void SetItem(Item* i);
	Item* GrabItem();
	Item* GrabItem(Item* i);

	bool isSlotEmpty() { return (isEmpty); }

	SlotRegion GetSlotRegion() { return *slotRegion; }
private:

	bool isEmpty;
	sf::Texture* emptySlotText;
	Item* item;
	SlotRegion* slotRegion;
};

