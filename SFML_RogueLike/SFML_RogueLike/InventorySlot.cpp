#include "InventorySlot.h"

InventorySlot::InventorySlot()
	:	UIComponent(sf::Vector2f(75, 75), sf::Vector2f()),
		item(nullptr),
		slotRegion(new SlotRegion(SlotRegion::none)),
		itemDescriptionText(new sf::Text()),
		cursorInBox(false)
{
	emptySlotTexture = new sf::Texture();
	emptySlotTexture->loadFromFile("Art/UI/EmptySlot.png");
	box.setTexture(emptySlotTexture);

	isEmpty = true;
	sf::Font* font = new sf::Font();
	font->loadFromFile("Fonts/04B_30.TTF");
	itemDescriptionText->setFont(*font);
	itemDescriptionText->setCharacterSize(20);
}

InventorySlot::InventorySlot(SlotRegion* sr)
	:	InventorySlot()
{	
	slotRegion = new SlotRegion(*sr);
}

InventorySlot::InventorySlot(Item* i)
	:	InventorySlot()
{
	item = i;
	if (item == nullptr)
		isEmpty = true;
	else
	{
		isEmpty = false;
		itemDescriptionText->setString(item->GetItemStatsFormatted());
	}
		
}

void InventorySlot::Update(sf::Vector2f mousePos)
{
	cursorInBox = box.getGlobalBounds().contains(mousePos);

	if (!isEmpty)
	{
		item->SetPosition(box.getPosition());
		itemDescriptionText->setPosition(mousePos);
	}
}

void InventorySlot::Draw(sf::RenderWindow& window)
{
	UIComponent::Draw(window);
	if (!isEmpty && item != nullptr)
	{
		item->Draw(window);
	}
}

void InventorySlot::DrawDescp(sf::RenderWindow& window)
{
	if (cursorInBox)
		window.draw(*itemDescriptionText);
}

void InventorySlot::Deleteitem()
{
	itemDescriptionText->setString("");
	delete item; 
	item = nullptr;
	isEmpty = true;
}

void InventorySlot::SetItem(Item* i)
{
	if (i != nullptr)
	{
		item = i;
		isEmpty = false;
		itemDescriptionText->setString(item->GetItemStatsFormatted());
	}
}

Item* InventorySlot::GrabItem()
{
	item->GetItemBox().setTexture(nullptr);
	isEmpty = true;
	Item* temp = item->Clone();
	delete item;
	item = nullptr;
	itemDescriptionText->setString("");

	return temp;
}

Item* InventorySlot::GrabItem(Item* i)
{
	Item* temp = new Item(*item);
	item = new Item(*i);
	itemDescriptionText->setString(item->GetItemStats());

	return temp;
}
