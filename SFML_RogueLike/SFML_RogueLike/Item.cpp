#include "Item.h"

Item::Item(sf::Texture* itemText)
	:	itemBox(sf::Vector2f(100, 100)),
		itemName("Default")
{
	itemBox.setTexture(itemText);

	itemBox.setOrigin(itemBox.getSize() / 2.0f);
}

Item::Item(sf::Texture* itemText, std::string name)
	:	itemBox(sf::Vector2f(100, 100)),
		itemName(name)
{
	itemBox.setTexture(itemText);

	itemBox.setOrigin(itemBox.getSize() / 2.0f);
}

Item::~Item()
{
}

void Item::SetPosition(sf::Vector2f pos)
{
	itemBox.setPosition(pos);
}

void Item::Draw(sf::RenderWindow& window)
{
	window.draw(itemBox);
}
