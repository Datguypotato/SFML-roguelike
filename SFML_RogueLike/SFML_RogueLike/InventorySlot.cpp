#include "InventorySlot.h"

InventorySlot::InventorySlot()
	:	UIComponent(sf::Vector2f(75, 75), sf::Vector2f()),
		item(nullptr),
		slotRegion(new SlotRegion(SlotRegion::none))
{
	emptySlotText = new sf::Texture();
	emptySlotText->loadFromFile("Art/UI/EmptySlot.png");
	box.setTexture(emptySlotText);

	isEmpty = true;
}

InventorySlot::InventorySlot(SlotRegion* sr)
	:	UIComponent(sf::Vector2f(75, 75), sf::Vector2f()),
		item(nullptr),
		slotRegion(new SlotRegion(*sr))
{
	emptySlotText = new sf::Texture();
	emptySlotText->loadFromFile("Art/UI/EmptySlot.png");
	box.setTexture(emptySlotText);

	isEmpty = true;
}

InventorySlot::InventorySlot(Item* i)
	:	UIComponent(sf::Vector2f(75, 75), sf::Vector2f()),
		item(i),
		slotRegion(new SlotRegion(SlotRegion::none))
{
	emptySlotText = new sf::Texture();
	emptySlotText->loadFromFile("Art/UI/EmptySlot.png");

	box.setTexture(emptySlotText);

	if (item == nullptr)
		isEmpty = true;
	else
		isEmpty = false;
}

void InventorySlot::Update(sf::RectangleShape player)
{
	if(!isEmpty)
		item->SetPosition(box.getPosition());
}

void InventorySlot::Draw(sf::RenderWindow& window)
{
	UIComponent::Draw(window);
	if (!isEmpty && item != nullptr)
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
	item = nullptr;

	return temp;
}

Item* InventorySlot::GrabItem(Item* i)
{
	Item* temp = new Item(*item);
	item = new Item(*i);

	return temp;
}
