#pragma once
#include <SFML/Graphics.hpp>

class GridNode
{
public:
	GridNode(sf::Vector2i position, GridNode* cameFrom);
	~GridNode();

	GridNode* GetCameFrom() { return cameFrom; }

protected:
	GridNode* cameFrom;
	sf::Vector2f position;
};

