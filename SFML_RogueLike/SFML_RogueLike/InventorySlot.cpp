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

void InventorySlot::Draw(sf::RenderWindow& window)
{
	UIComponent::Draw(window);
	if (!isEmpty)
	{
		item->Draw(window);
	}
}


void InventorySlot::SetItem(Item* i)
{
	item = i;
	isEmpty = false;
}

Item* InventorySlot::GrabItem()
{
	item->GetItemBox().setTexture(nullptr);
	isEmpty = true;
	Item* temp = new Item(*item);
	delete item;

	return temp;
}

Item* InventorySlot::GrabItem(Item* i)
{
	Item* temp = new Item(*item);
	item = new Item(*i);

	return temp;
}
