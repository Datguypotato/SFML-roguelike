#pragma once
#include <SFML/Graphics.hpp>

class GridNode
{
public:
	GridNode(sf::Vector2i position, GridNode* cameFrom);
	~GridNode();

	GridNode* GetCameFrom() { return cameFrom; }
	sf::Vector2i GetPosition() { return position; }

	std::vector<sf::Vector2i> GetConnections();

protected:
	GridNode* cameFrom;
	sf::Vector2i position;	
};

