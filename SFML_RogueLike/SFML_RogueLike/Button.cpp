#include "Button.h"

Button::Button(sf::Vector2f size, sf::Vector2f pos, std::function<void(sf::RectangleShape box)> callBack, sf::Texture* buttonText)
	:	UIComponent(size, pos),
		isClickable(true)
{
	callbacks = callBack;
	box.setTexture(buttonText);
	
	e = new TimeEvent(std::bind(&Button::SetClickable, this), 0.3f, true, "ClickAble");
	e->Pause();
	
}

void Button::OnClick(sf::Vector2f mousePos)
{
	if (CursorIsInBox(mousePos))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && isClickable && isDrawing)
		{
			ClickAction();
		}
	}
}

void Button::ClickAction()
{
	//callbacks(box);
	isClickable = false;
	e->Play();
	callbacks(box);
}

void Button::SetClickable()
{
	isClickable = true;
}
