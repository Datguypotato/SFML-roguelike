#include "Button.h"

Button::Button(sf::Vector2f size, sf::Vector2f pos, std::function<void()> callBack)
	:	UIComponent(size)
{
	callbacks = callBack;
	box.setPosition(pos);
	box.setFillColor(sf::Color::Red);
}

Button::~Button()
{
}

void Button::SetPosition(sf::Vector2f pos)
{
	UIComponent::SetPosition(pos);
}

void Button::OnClick()
{
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
		callbacks();
}
