#include "Inventory.h"

Inventory::Inventory(sf::RectangleShape* p)
:	isOpen(false),
	isDrawing(false),
	slotCount(3),
	slotStartingPos(sf::Vector2f(500, 200)),
	equipSlotStartingPos(sf::Vector2f(-500, 200)),
	currItem(nullptr),
	canInteract(true)
{
	player = p;
	SetupSlots();

	timedEvent = new TimeEvent(std::bind(&Inventory::SetOpenable, this), 0.5f, true);
	timedEvent->Pause();
}

void Inventory::OpenClose()
{
	isOpen = !isOpen;

	std::cout << "The inventory is now " << isOpen << std::endl;
}

void Inventory::Update(sf::Vector2f mousePos, Weapon* weapon)
{
	if (isDrawing)
	{
		int i = 0;
		for (InventorySlot* slot : *slots)
		{
			float xPos = (slot->GetSize().x * (float)i) + 10 * (float)i;
			slot->SetPosition(player->getPosition() - slotStartingPos + sf::Vector2f(xPos, 0));
			slot->Update(*player);
			i++;
		}

		i = 0;
		for (InventorySlot* slot : *equipSlots)
		{
			float yPos = (slot->GetSize().y * (float)i) + 10 * (float)i;
			slot->SetPosition(player->getPosition() - equipSlotStartingPos + sf::Vector2f(0, yPos));
			slot->Update(*player);
			i++;
		}

		trashBin->SetPosition(player->getPosition() - sf::Vector2f(-500, -200));

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && isDrawing && canInteract)
		{
			for (InventorySlot* slot : *slots)
			{
				OnClick(mousePos, slot);

				//std::cout << std::endl;
			}

			for (InventorySlot* slot : *equipSlots)
			{
				OnClick(mousePos, slot);
				if(slot->CursorIsInBox(mousePos))
					weapon->UpdateItems(GetCurrEquipItem());
			}
			canInteract = false;
			timedEvent->Play();

			//if (currItem != nullptr)
			//	std::cout << "Current item: " << currItem->GetName() << std::endl;

			if (trashBin->CursorIsInBox(mousePos))
			{
				delete currItem;
				currItem = nullptr;
			}
				
		}


		if (currItem != nullptr)
			currItem->SetPosition(mousePos);

		isDrawing = false;
	}
}

void Inventory::GetItem(Item* i)
{
	for (InventorySlot* slot : *slots)
	{
		if (slot->isSlotEmpty())
		{
			slot->SetItem(i);
			break;
		}

		std::cout << "inventory is full\n";
	}
}

bool Inventory::isFull()
{
	bool full = true;
	for (InventorySlot* slot : *slots)
	{
		if (slot->isSlotEmpty())
		{
			full = false;
			break;
		}
	}

	return full;
}

std::vector<Item*> Inventory::GetCurrEquipItem()
{
	std::vector<Item*> i = std::vector<Item*>();

	for (InventorySlot* slot : *equipSlots)
	{
		i.push_back(slot->GetItem());
	}

	return i;
}

void Inventory::SetupSlots()
{
	slots = new std::vector<InventorySlot*>();
	equipSlots = new std::vector<InventorySlot*>();
	trashBin = new InventorySlot();

	for (int i = 0; i < slotCount; i++)
	{
		slots->push_back(new InventorySlot());
		equipSlots->push_back(new InventorySlot());
	}

}

void Inventory::OnClick(sf::Vector2f mousePos, InventorySlot* slot)
{
	if (slot->CursorIsInBox(mousePos))
	{
		if (!slot->isSlotEmpty() && currItem == nullptr)
			currItem = slot->GrabItem();
		else if (slot->isSlotEmpty() && currItem != nullptr)
		{
			slot->SetItem(new Item(*currItem));
			currItem = nullptr;
		}
		else if (!slot->isSlotEmpty() && currItem != nullptr)
		{
			Item* temp = new Item(*currItem);
			currItem = slot->GetItem();
			slot->SetItem(temp);
			//std::cout << "Swap Item\n";
		}
	}
}

void Inventory::Draw(sf::RenderWindow& window)
{
	isDrawing = true;
	if (isOpen)
	{
		for (InventorySlot* slot : *slots)
		{
			slot->Draw(window);
		}

		for (InventorySlot* slot : *equipSlots)
		{
			slot->Draw(window);
		}

		trashBin->Draw(window);
	}
	if (currItem != nullptr)
		currItem->Draw(window);
}