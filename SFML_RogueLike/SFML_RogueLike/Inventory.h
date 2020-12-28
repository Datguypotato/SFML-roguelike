#pragma once
#include <SFML/Graphics.hpp>

#include "TimeEvent.h"
#include "Player.h"
#include "Item.h"
#include "InventorySlot.h"

class Inventory
{
public: 
	Inventory(Player* p);

	void OpenClose();

	void Update(sf::Vector2f mousePos);
	void Draw(sf::RenderWindow& window);

	TimeEvent* GetEvent() { return timedEvent; }
	void SetOpenable() { canInteract = true; };
private:
	void OnClick(sf::Vector2f mousePos);

	Player* player;

	bool canInteract;
	bool isOpen;
	int slotCount;
	Item* currItem;
	sf::Vector2f slotStartingPos;
	std::vector<InventorySlot*>* slots;

	bool isDrawing;
	TimeEvent* timedEvent;
};

