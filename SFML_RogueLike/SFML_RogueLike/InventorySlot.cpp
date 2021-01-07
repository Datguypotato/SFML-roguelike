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
	:	UIComponent(sf::Vector2f(75, 75), sf::Vector2f()),
		item(nullptr),
		slotRegion(new SlotRegion(*sr)),
		itemDescriptionText(new sf::Text()),
		cursorInBox(false)
{
	emptySlotTexture = new sf::Texture();
	emptySlotTexture->loadFromFile("Art/UI/EmptySlot.png");
	box.setTexture(emptySlotTexture);

	isEmpty = true;
}

InventorySlot::InventorySlot(Item* i)
	:	UIComponent(sf::Vector2f(75, 75), sf::Vector2f()),
		item(i),
		slotRegion(new SlotRegion(SlotRegion::none)),
		itemDescriptionText(new sf::Text()),
		cursorInBox(false)
{
	emptySlotTexture = new sf::Texture();
	emptySlotTexture->loadFromFile("Art/UI/EmptySlot.png");

	box.setTexture(emptySlotTexture);

	if (item == nullptr)
		isEmpty = true;
	else
		isEmpty = false;
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
	//TODO Cannot draw yet
	if (cursorInBox)
		window.draw(*itemDescriptionText);

}


void InventorySlot::SetItem(Item* i)
{
	item = i;
	isEmpty = false;
	itemDescriptionText->setString(item->GetItemStats());
	std::cout << item->GetItemStats();
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
	itemDescriptionText->setString(item->GetItemStats());

	return temp;
}

std::string InventorySlot::GetItemDescription()
{
	if (!isEmpty)
		return item->GetItemStats();

	return "";
}
