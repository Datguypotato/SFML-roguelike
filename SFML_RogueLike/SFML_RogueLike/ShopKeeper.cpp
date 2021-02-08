#include "ShopKeeper.h"

ShopKeeper::ShopKeeper(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position)
	:	Interactable(texture, size, position),
		amountSlot(6)
{
	ItemBuilder b = ItemBuilder();
	for (unsigned int i = 0; i < amountSlot; i++)
	{
		buySlots.push_back(new InventorySlot(b.BuildRandom()));
	}
}

void ShopKeeper::Update(float deltaTime, sf::Vector2f mousePos)
{
	if (isDrawing)
	{
		for (unsigned int i = 0; i < amountSlot; i++)
		{
			buySlots[i]->SetPosition(sf::Vector2f(100 * i, 0));
		}
	}
}

void ShopKeeper::Draw(sf::RenderWindow& window)
{
	Ground::Draw(window);

	if (InTrigger)
	{
		isDrawing = true;
		for (InventorySlot* slot : buySlots)
		{
			slot->Draw(window);
		}
	}
}
