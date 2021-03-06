#include "Item.h"

Item::Item(sf::Texture* itemText)
	:	itemBox(sf::Vector2f(100, 100)),
		itemName("Default"),
		slotRegion(new SlotRegion(SlotRegion::none)),
		upgradeItem(nullptr)
{
	itemBox.setTexture(itemText);
	itemBox.setOrigin(itemBox.getSize() / 2.0f);
	synergy = nullptr;
}

Item::Item(sf::Texture* itemText, std::string name)
	:	Item(itemText)
{
	itemName = name;
}

Item::Item(sf::Texture* itemText, std::string name, SlotRegion* sr)
	:	Item(itemText, name)
{
	slotRegion = sr;
}

Item::Item(sf::Texture* itemText, std::string name, SlotRegion* sr, Item* upgrade)
	:	Item(itemText, name, sr)
{
	upgradeItem = upgrade;
}

void Item::SetPosition(sf::Vector2f pos)
{
	itemBox.setPosition(pos);
}

void Item::Draw(sf::RenderWindow& window)
{
	window.draw(itemBox);
}

//TODO: Make all the item have abstract string function
std::string Item::GetItemStats()
{	
	std::string stats = std::string();
	stats += itemName + "\n";

	return stats;
}

std::string Item::GetItemStatsFormatted()
{
	std::string stat(GetItemStats());
	std::string formated = "";
	int space = 0;

	for (auto it = stat.begin(); it != stat.end(); it++)
	{
		formated += *it;

		if (*it == ' ')
			space++;

		if (space >= 3)
		{
			formated += "\n";
			space = 0;
		}
	}

	return formated;
}

