#pragma once
#include "UIComponent.h"
#include "Item.h"

// TODO: inherit from button instead?

class InventorySlot : public UIComponent
{
public:
	InventorySlot(Item* it);

	void Update(Player* player) override;

	void Draw(sf::RenderWindow& window);

	Item* GetItem() { return item; }
	void SetItem(Item* i);
	Item* GrabItem();
	Item* GrabItem(Item* i);

	bool isSlotEmpty() { return (isEmpty); }

private:
	Item* item;
	sf::Texture* emptySlotText;
	bool isEmpty;
};

