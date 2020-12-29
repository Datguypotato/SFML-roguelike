#include "Inventory.h"

Inventory::Inventory(Player* p)
	:	isOpen(false),
		isDrawing(false),
		slotCount(3),
		slotStartingPos(sf::Vector2f(500, 200)),
		currItem(nullptr),
		canInteract(true)
{
	player = p;
	slots = new std::vector<InventorySlot*>();

	std::string path;
	for (int i = 0; i < slotCount; i++)
	{
		sf::Texture* text = new sf::Texture();

		if (i == 0)
			path = "Art/UI/Frikandelbroodje.png";
		else if (i == 1)
			path = "Art/UI/1.png";
		else
			path = "Art/UI/2.png";
		text->loadFromFile(path);
		slots->push_back(new InventorySlot(new Item(text, std::to_string(i))));
	}

	timedEvent = new TimeEvent(std::bind(&Inventory::SetOpenable, this), 0.5f, true);
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
			slot->SetPosition(player->GetPosition() - slotStartingPos + (sf::Vector2f(xPos, 0)));
			slot->Update(player);
			i++;
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && isDrawing && canInteract)
		{
			OnClick(mousePos);
		}


		if (currItem != nullptr)
			currItem->SetPosition(mousePos);

		isDrawing = false;
	}
}

void Inventory::OnClick(sf::Vector2f mousePos)
{
	for (InventorySlot* slot : *slots)
	{
		if (slot->CursorIsInBox(mousePos) && slot->GetDrawnStatus())
		{
			if (!slot->isSlotEmpty() && currItem == nullptr)
				currItem = slot->GrabItem();
			else if(slot->isSlotEmpty() && currItem != nullptr)
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


		if (!slot->isSlotEmpty())
		{
			std::cout << slot->GetItem()->GetName() << "  ";
		}
		else
			std::cout << "Empty" << "  ";
	}
	std::cout << std::endl;
	canInteract = false;

	if (currItem != nullptr)
		std::cout << "Current item: " << currItem->GetName() << std::endl;

	timedEvent->Play();
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
	}
	if (currItem != nullptr)
		currItem->Draw(window);
}


