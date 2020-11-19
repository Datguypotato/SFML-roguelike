#pragma once
#include <functional>
#include "UIComponent.h"

class Button : public UIComponent
{
public:
	Button(sf::Vector2f size, sf::Vector2f pos, std::function<void(sf::RectangleShape box)> callBack);
	~Button();

	void SetPosition(sf::Vector2f pos);
	void OnClick();


protected:
	std::function<void(sf::RectangleShape box)> callbacks;
};

