#include "ItemButton.h"

ItemButton::ItemButton(Item* i, sf::Vector2f pos, std::function<void(sf::RectangleShape box)> callBack, sf::Texture* texture, Player* p)
	:	Button(sf::Vector2f(350, 500), pos, callBack, texture),
		item(i),
		player(p)
{
	sf::Font* font = new sf::Font();
	font->loadFromFile("Fonts/04B_30.TTF");
	text = new sf::Text(item->GetItemStats(), *font, 13);
	sf::FloatRect rect = text->getLocalBounds();
	text->setOrigin(rect.left + rect.width / 2.0f,
					rect.top + rect.height / 2.0f);
}

void ItemButton::Update(sf::RectangleShape player)
{
	UIComponent::Update(player);
	item->SetPosition(box.getPosition() - sf::Vector2f(0, 50));
	text->setPosition(box.getPosition() - sf::Vector2f(0, -120));
}

void ItemButton::ClickAction()
{
	// TODO: Give player item and resume game
	std::cout << "Clicked\n";
	player->GetInventory()->GetItem(item);
	Button::ClickAction();
}

void ItemButton::Draw(sf::RenderWindow& window)
{
	Button::Draw(window);
	item->Draw(window);
	window.draw(*text);
}
