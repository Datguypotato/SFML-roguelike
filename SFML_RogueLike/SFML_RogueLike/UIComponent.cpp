#include "UIComponent.h"


UIComponent::UIComponent(sf::Vector2f size)
{
	box = sf::RectangleShape(size);
	box.setOrigin(box.getSize() / 2.0f);
	halfSize = box.getSize() / 2.0f;
}

UIComponent::~UIComponent()
{
}

bool UIComponent::CursorIsInBox(sf::Vector2f mousePos)
{
	return (box.getGlobalBounds().contains(mousePos));
}

void UIComponent::Draw(sf::RenderWindow& window)
{
	window.draw(box);
}