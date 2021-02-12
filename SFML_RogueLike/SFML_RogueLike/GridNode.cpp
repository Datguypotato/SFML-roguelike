#include "GridNode.h"

GridNode::GridNode(sf::Vector2i position, GridNode* cameFrom)
	:	position(position),
		cameFrom(cameFrom)
{
}

GridNode::~GridNode()
{
	if (cameFrom != nullptr)
	{
		delete cameFrom;
		cameFrom = nullptr;
	}
}
