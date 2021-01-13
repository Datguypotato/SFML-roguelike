#include "Inventory.h"

Inventory::Inventory(sf::RectangleShape* p, Weapon* w)
:	isOpen(false),
	isDrawing(false),
	slotCount(3),
	slotStartingPos(sf::Vector2f(500, 200)),
	equipSlotStartingPos(sf::Vector2f(-500, 200)),
	currItem(nullptr),
	canInteract(true),
	weapon(w)
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

void Inventory::Update(sf::Vector2f mousePos)
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
				case SlotRegion::Weapon:
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

		weapon->SetWeapon(GetCurrEquipItem()[0]);
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
	CheckifCanCombine();
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
	slotregions.push_back(SlotRegion::Weapon);
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

	// put all items in one single vector
	std::vector<InventorySlot*> currentItems = std::vector<InventorySlot*>();
	for (InventorySlot* slot : *equipSlots)
	{
		if(!slot->isSlotEmpty())
			currentItems.push_back(slot);
	}
	for (InventorySlot* slot : *slots)
	{
		if (!slot->isSlotEmpty())
			currentItems.push_back(slot);
	}

	if (currentItems.size() < 3)
		return;

	std::vector<std::pair<InventorySlot*, int>> itemPairs = std::vector<std::pair<InventorySlot*, int>>();

	//std::vector<std::pair<std::string, int>> itemPairs = std::vector<std::pair<std::string, int>>();
	for (InventorySlot* currentSlots : currentItems)
	{
		if (itemPairs.size() == 0)
			itemPairs.push_back(std::pair<InventorySlot*, int>(currentSlots, 0));

		for (std::pair<InventorySlot*, int>& pair : itemPairs)
		{
			if (currentSlots->GetItem()->GetName() == pair.first->GetItem()->GetName())
			{
				++pair.second;
				std::cout << pair.second << std::endl;
			}
			else
				itemPairs.push_back(std::pair<InventorySlot*, int>(currentSlots, 1));
		}
	}

	for (std::pair<InventorySlot*, int> pair : itemPairs)
	{
		if (pair.second >= 3)
		{
			Item* upgrade = nullptr;
			std::string targetItem;

			if (upgrade == nullptr) // check lootmanager for spelling mistakes
			{
				upgrade = pair.first->GetItem()->GetUpgrade();
				targetItem = pair.first->GetItem()->GetName();
			}

			for (InventorySlot* slot : currentItems)
			{
				if (slot->GetItem()->GetName() == targetItem)
					slot->Deleteitem();
			}

			bool found = false;
			for (InventorySlot* slot : *equipSlots)
			{
				if (!found && slot->GetSlotRegion() == upgrade->GetSlotRegion())
				{
					slot->SetItem(upgrade);
					
					found = true;
				}
			}
		}
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
			slot->SetItem(currItem->Clone());
			delete currItem;
			currItem = nullptr;
		}
		else if (!slot->isSlotEmpty() && currItem != nullptr)
		{
			Item* temp = currItem->Clone();
			currItem = slot->GetItem();
			slot->SetItem(temp);
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

		if (currItem != nullptr)
			currItem->Draw(window);
	}

}