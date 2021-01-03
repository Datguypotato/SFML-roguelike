#include "Button.h"

Button::Button(sf::Vector2f size, sf::Vector2f pos, std::function<void(sf::RectangleShape box)> callBack, sf::Texture* buttonText)
	:	UIComponent(size, pos),
		isClickable(true)
{
	callbacks = callBack;
	box.setTexture(buttonText);
	
	e = new TimeEvent(std::bind(&Button::SetClickable, this), 0.3f, true);
	e->Pause();
	
}

void Button::Update(sf::RectangleShape player)
{
}

void Button::OnClick()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && isClickable && isDrawing)
	{
		callbacks(box);
		isClickable = false;
		e->Play();
	}
}

void Button::SetClickable()
{
	isClickable = true;
}
