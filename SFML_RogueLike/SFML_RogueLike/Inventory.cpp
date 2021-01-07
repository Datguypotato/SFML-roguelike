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

	timedEvent = new TimeEvent(std::bind(&Inventory::SetOpenable, this), 0.5f, true, "Open");
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
			slot->Update(mousePos);
			i++;
		}

		i = 0;
		for (InventorySlot* slot : *equipSlots)
		{
			float yPos = (slot->GetSize().y * (float)i) + 10 * (float)i;
			slot->SetPosition(player->getPosition() - equipSlotStartingPos + sf::Vector2f(0, yPos));
			slot->Update(mousePos);
			i++;
		}

		trashBin->SetPosition(player->getPosition() - sf::Vector2f(-500, -200));

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && isDrawing && canInteract)
		{
			for (InventorySlot* slot : *slots)
			{
				OnClick(mousePos, slot);
			}

			int index = 0;
			for (InventorySlot* slot : *equipSlots)
			{
				OnClickEquipment(mousePos, slot, index);
				index++;
				if(slot->CursorIsInBox(mousePos))
					weapon->UpdateItems(GetCurrEquipItem());
			}
			canInteract = false;
			timedEvent->Play();

			if (currItem != nullptr)
			{
				std::string region;
				
				switch (currItem->GetSlotRegion())
				{
				case SlotRegion::none:
					region = "None";
					break;
				case SlotRegion::head:
					region = "Head";
					break;
				case SlotRegion::body:
					region = "Body";
					break;
				case SlotRegion::legs:
					region = "Legs";
					break;
				default:
					region = "Unkown";
					break;
				}

				std::cout << "Current item " << region << std::endl;
			}
				

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

	std::vector<SlotRegion> slotregions;
	slotregions.push_back(SlotRegion::head);
	slotregions.push_back(SlotRegion::body);
	slotregions.push_back(SlotRegion::legs);
	for (int i = 0; i < slotCount; i++)
	{
		slots->push_back(new InventorySlot());
		equipSlots->push_back(new InventorySlot(&slotregions[i]));
	}

}

void Inventory::OnClickEquipment(sf::Vector2f mousePos, InventorySlot* slot, int index)
{
	if (slot->CursorIsInBox(mousePos))
	{
		if (currItem != nullptr && currItem->GetSlotRegion() != slot->GetSlotRegion())
		{
			return;
		}
		else
			OnClick(mousePos, slot);
	}
}

void Inventory::CheckifCanCombine()
{
	//TODO not priority

	//std::vector<Item*> currentItems = std::vector<Item*>();
	//for (InventorySlot* slot : *equipSlots)
	//{
	//	if(!slot->isSlotEmpty())
	//		currentItems.push_back(slot->GetItem());
	//}
	//for (InventorySlot* slot : *slots)
	//{
	//	if (!slot->isSlotEmpty())
	//		currentItems.push_back(slot->GetItem());
	//}

	//if (currentItems.size() < 3)
	//	return;

	//for (Item* currentItem : currentItems)
	//{

	//}
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
			std::cout << "Swap Item\n";
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

		for (InventorySlot* slot : *slots)
			slot->DrawDescp(window);

		for (InventorySlot* slot : *equipSlots)
			slot->DrawDescp(window);

		trashBin->Draw(window);
	}
	if (currItem != nullptr)
		currItem->Draw(window);
}