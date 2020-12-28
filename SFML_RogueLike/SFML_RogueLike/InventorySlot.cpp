#include "InventorySlot.h"

InventorySlot::InventorySlot(Item* i)
	:	UIComponent(sf::Vector2f(75, 75), sf::Vector2f()),
		item(i)
{
	emptySlotText = new sf::Texture();
	emptySlotText->loadFromFile("Art/UI/EmptySlot.png");

	box.setTexture(emptySlotText);

	if (item == nullptr)
		isEmpty = true;
	else
		isEmpty = false;
}

void InventorySlot::Update(Player* player)
{
	if(!isEmpty)
		item->SetPosition(box.getPosition());
}


void InventorySlot::SetItem(Item* i)
{
	item = i;
	isEmpty = false;
}

Item* InventorySlot::GrabItem()
{
	item->GetItemBox().setTexture(nullptr);
	//item = nullptr;
	isEmpty = true;

	return item;
}

Item* InventorySlot::GrabItem(Item* i)
{
	Item* temp = item;
	item = i;

	return temp;
}
