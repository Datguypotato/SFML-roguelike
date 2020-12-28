#include "UIComponent.h"


UIComponent::UIComponent(sf::Vector2f size, sf::Vector2f pos)
	:	position(pos),
		isDrawing(false)
{
	box = sf::RectangleShape(size);
	box.setOrigin(box.getSize() / 2.0f);
	this->size = size;
	halfSize = box.getSize() / 2.0f;
}

UIComponent::~UIComponent()
{
}

bool UIComponent::CursorIsInBox(sf::Vector2f mousePos)
{
	return (box.getGlobalBounds().contains(mousePos));
}

void UIComponent::CanUpdate(Player* player)
{
	if (isDrawing)
	{
		Update(player);
		box.setPosition(player->GetPosition() - position);
	}
}

void UIComponent::Update(Player* player)
{
}


void UIComponent::Draw(sf::RenderWindow& window)
{
	window.draw(box);
	isDrawing = true;
}