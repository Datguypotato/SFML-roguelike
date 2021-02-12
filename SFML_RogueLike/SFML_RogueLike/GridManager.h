#pragma once
#include <SFML/Graphics.hpp>

#include "GridNode.h"

class GridManager
{
public:
	GridManager(sf::RectangleShape body);
	

protected:
	std::vector<GridNode*> nodes;
	sf::RectangleShape AIbody;
};

