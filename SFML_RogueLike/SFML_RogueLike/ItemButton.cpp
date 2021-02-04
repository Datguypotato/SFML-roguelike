#include "ItemButton.h"

ItemButton::ItemButton(Item* i, sf::Vector2f pos, std::function<void(sf::RectangleShape box)> callBack, sf::Texture* texture)
	:	Button(sf::Vector2f(200, 500), pos, callBack, texture),
		item(i)
{
}

void ItemButton::OnClick(sf::Vector2f mousePos)
{
	Button::OnClick(mousePos);
	if (CursorIsInBox(mousePos))
	{
		std::cout << "Clicked\n";
	}
}
