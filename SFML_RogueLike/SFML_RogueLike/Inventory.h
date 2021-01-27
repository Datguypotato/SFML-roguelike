#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "TimeEvent.h"
#include "Item.h"
#include "InventorySlot.h"
#include "Weapon.h"
#include "Armour.h"

class Inventory
{
public: 
	Inventory(sf::RectangleShape* p, Weapon* w, Armour* a);

	void OpenClose();

	void Update(sf::Vector2f mousePos);
	void GetItem(Item* i);
	bool isFull();
	void Draw(sf::RenderWindow& window);

	TimeEvent* GetEvent() { return timedEvent; }
	void SetOpenable() { canInteract = true; };

	std::vector<Item*> GetCurrEquipItem();
private:
	void SetupSlots();
	void OnClick(sf::Vector2f mousePos, InventorySlot* slot);
	void OnClickEquipment(sf::Vector2f mousePos, InventorySlot* slot, int index);

	void AddNewItem(Item* i);
	void CheckifCanCombine();

	sf::RectangleShape* player;
	Weapon* weapon;
	Armour* armour;

	bool canInteract;
	bool isOpen;
	int slotCount;
	Item* currItem;
	sf::Vector2f slotStartingPos;
	sf::Vector2f equipSlotStartingPos;
	std::vector<InventorySlot*>* slots;
	std::vector<InventorySlot*>* equipSlots;
	InventorySlot* trashBin;
	std::vector<std::pair<Item*, int>*> itemPairs;

	bool isDrawing;
	TimeEvent* timedEvent;
};

