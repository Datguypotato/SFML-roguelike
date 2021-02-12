#include "ShopKeeper.h"

ShopKeeper::ShopKeeper(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, Player* p)
	:	Interactable(texture, size, position),
		amountSlot(6),
		player(p)
{
	ItemBuilder b = ItemBuilder();
	for (unsigned int i = 0; i < amountSlot; i++)
	{
		buySlots.push_back(new InventorySlot(b.BuildRandom()));
	}

	sf::Texture* panelTexture = new sf::Texture();
	panelTexture->loadFromFile("Art/ShopkeeperPanel.png");
	backgroundPanel = sf::RectangleShape(sf::Vector2f(800, 560));
	backgroundPanel.setOrigin(backgroundPanel.getSize() / 2.0f);
	backgroundPanel.setTexture(panelTexture);
}

//TODO: Add differnt buy condition when wearing the right equipment
void ShopKeeper::Update(float deltaTime, sf::Vector2f mousePos, sf::Vector2f playerPos)
{
	if (isDrawing)
	{
		if (buySlots.empty())
			return;

		buySlots[0]->SetPosition(playerPos + sf::Vector2f(-100, 50) * 1.5f);
		buySlots[1]->SetPosition(playerPos + sf::Vector2f(0, 50) * 1.5f);
		buySlots[2]->SetPosition(playerPos + sf::Vector2f(100, 50) * 1.5f);

		buySlots[3]->SetPosition(playerPos + sf::Vector2f(-100, -50) * 1.5f);
		buySlots[4]->SetPosition(playerPos + sf::Vector2f(0, -50) * 1.5f);
		buySlots[5]->SetPosition(playerPos + sf::Vector2f(100, -50) * 1.5f);

		backgroundPanel.setPosition(playerPos);

		for (InventorySlot* slot : buySlots)
			slot->Update(mousePos);

		bool hasCollected = false;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			for (InventorySlot* slot : buySlots)
			{
				if (slot->CursorIsInBox(mousePos))
				{
					if (!hasCollected)
					{
						player->CollectItem(slot->GetItem());
						hasCollected = true;
						break;
					}
				}
			}

			if (hasCollected)
			{
				for (InventorySlot* slot : buySlots)
				{
					delete slot;					
				}
				buySlots.clear();
			}
		}

	}
}

void ShopKeeper::Draw(sf::RenderWindow& window)
{
	Ground::Draw(window);

	if (InTrigger)
	{
		isDrawing = true;

		window.draw(backgroundPanel);

		for (InventorySlot* slot : buySlots)
		{
			slot->Draw(window);
		}

		for (InventorySlot* slot : buySlots)
		{
			slot->DrawDescp(window);
		}

	}
}
