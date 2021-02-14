#include "GridManager.h"

GridManager::GridManager(Entity* t)
	:	target(t),
		nodes(std::vector<GridNode*>()),
		allNodes(std::vector<GridNode*>()),
		targetsToCheck(std::vector<sf::Vector2i>())
{
}

std::vector<sf::Vector2i> GridManager::GenerateMap(std::vector<Collider*> colliders, sf::Vector2i startingPos)
{
	// TODO
	bool foundPath = false;
	sf::Vector2i targetposition = sf::Vector2i(500, 600);
	allNodes.clear();

	while (!foundPath)
	{
		std::vector<GridNode*> newTargets = std::vector<GridNode*>();

		if (nodes.empty())
		{
			nodes.push_back(new GridNode(startingPos, nullptr)); // create the starting node
			allNodes.push_back(nodes[0]);
		}

		for (GridNode* targetNode : nodes)
		{
			if (foundPath)
				break;

			targetsToCheck.clear();
			for (sf::Vector2i connection : targetNode->GetConnections())
			{
				targetsToCheck.push_back(connection);
			}

			for (sf::Vector2i target : targetsToCheck)
			{
				if (target == targetposition)
				{
					newTargets.push_back(new GridNode(target, targetNode));
					foundPath = true;
					break;
				}

				bool isInWall = false;
				for (Collider* coll : colliders)
				{
					if (coll->CheckTrigger(static_cast<sf::Vector2f>(target)))
					{
						isInWall = true;
					}
				}

				if (!isInWall)
				{
					GridNode* g = new GridNode(target, targetNode);
					newTargets.push_back(g);
					allNodes.push_back(g);
				}
			}			
		}
		nodes.clear();
		for (GridNode* newNodes : newTargets)
		{
			nodes.push_back(newNodes);
		}
	}


	// Create path
	GridNode* node = nodes[nodes.size() - 1];
	std::vector<sf::Vector2i> path = std::vector<sf::Vector2i>();
	path.push_back(node->GetPosition());
	std::cout << "Path: x: " << node->GetPosition().x << " y: " << node->GetPosition().y << std::endl;
	while (node->GetCameFrom() != nullptr)
	{
		path.push_back(node->GetCameFrom()->GetPosition());
		node = node->GetCameFrom();
		std::cout << "Path: x: " << node->GetPosition().x << " y: " << node->GetPosition().y << std::endl;
	}

	// delete all nodes
	for (GridNode* node : allNodes)
	{
		delete node;
		node = nullptr;
	}
	allNodes.clear();

	return path;
}
