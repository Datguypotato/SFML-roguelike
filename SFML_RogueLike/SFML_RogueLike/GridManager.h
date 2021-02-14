#pragma once
#include <SFML/Graphics.hpp>

#include "Entity.h"
#include "GridNode.h"
#include "Collider.h"
/// <summary>
/// AI for the enemey
/// see this article to see how I implemented this
/// https://www.redblobgames.com/pathfinding/a-star/introduction.html
/// </summary>
class GridManager
{
public:
	GridManager(Entity* t);
	std::vector<sf::Vector2i> GenerateMap(std::vector<Collider*> colliders, sf::Vector2i startingPos);
	
	void SetTarget(Entity* a_Target) { target = a_Target; }

protected:
	std::vector<GridNode*> allNodes;
	std::vector<GridNode*> nodes;
	std::vector<sf::Vector2i> targetsToCheck;
	Entity* target;
};

