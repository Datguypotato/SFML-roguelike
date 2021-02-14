#include "GridNode.h"

GridNode::GridNode(sf::Vector2i position, GridNode* cameFrom)
	:	position(position),
		cameFrom(cameFrom)
{
}

GridNode::~GridNode()
{
	//if (cameFrom != nullptr)
	//{
	//	delete cameFrom;
	//	cameFrom = nullptr;
	//}
}

std::vector<sf::Vector2i> GridNode::GetConnections()
{
	std::vector<sf::Vector2i> connections = std::vector<sf::Vector2i>();
	connections.push_back(position + sf::Vector2i(-1, 0) * 100);
	connections.push_back(position + sf::Vector2i(0, -1) * 100);
	connections.push_back(position + sf::Vector2i(1, 0) * 100);
	connections.push_back(position + sf::Vector2i(0, 1) * 100);

	if (cameFrom != nullptr)
	{
		for (auto i = connections.begin(); i < connections.end(); i++)
		{
			if (*i == cameFrom->position)
			{
				connections.erase(i);
				break;
			}
		}
	}

	return connections;
}
