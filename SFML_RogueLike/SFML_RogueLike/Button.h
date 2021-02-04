#pragma once
#include <functional>

#include "UIComponent.h"
#include "TimeEvent.h"

class Button : public UIComponent
{
public:
	Button(sf::Vector2f size, sf::Vector2f pos, std::function<void(sf::RectangleShape box)> callBack, sf::Texture* buttonText);

	void Update(sf::RectangleShape player) override;
	void OnClick(sf::Vector2f mousePos);

	TimeEvent* GetEvent() { return e; }

protected:
	void SetClickable();

	TimeEvent* e;
	std::function<void(sf::RectangleShape box)> callbacks;
	bool isClickable;
};

