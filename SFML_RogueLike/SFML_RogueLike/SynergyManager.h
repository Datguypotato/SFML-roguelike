#pragma once
#include "Entity.h"
#include "Weapon.h"
#include "Armour.h"
#include "Item.h"
#include "TimeEvent.h"

#include <functional>

class SynergyManager
{
public:
	SynergyManager(Weapon* w, Armour* a);

	void Update(float deltaTime);

	void CheckSynergies(std::vector<Item*> currentlyEquiped);

	void OnStartLevel(Entity* player);
	void OnEndLevel();

	void OnSuccesfullAttack();
	void PlayerHit();

private:
	void AddAttackSpeedBuff();

	Weapon* playerWeapon;
	Armour* playerArmour;

	int reds;
	int blues;
	int greens;

	int extraAD;
	int extraAS;

	std::vector<TimeEvent*> timedEvents;
};

