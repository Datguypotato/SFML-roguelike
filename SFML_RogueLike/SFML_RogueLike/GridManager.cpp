#include "GridManager.h"

GridManager::GridManager(sf::RectangleShape body)
	:	AIbody(body),
		nodes(std::vector<GridNode*>())
{
}
