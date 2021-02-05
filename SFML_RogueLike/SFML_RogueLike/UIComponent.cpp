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

void UIComponent::CanUpdate(sf::RectangleShape player)
{
	if (isDrawing)
	{
		Update(player);
	}
}

void UIComponent::Update(sf::RectangleShape player)
{
	box.setPosition(player.getPosition() - position);
}


void UIComponent::Draw(sf::RenderWindow& window)
{
	window.draw(box);
	isDrawing = true;
}