#include "SynergyManager.h"

SynergyManager::SynergyManager(Weapon* w, Armour* a)
	:	reds(0),
		blues(0),
		greens(0),
		playerWeapon(w),
		playerArmour(a),
		extraAD(0),
		extraAS(0)
{
	timedEvents.push_back(new TimeEvent(std::bind(&SynergyManager::AddAttackSpeedBuff, this), 10, false, "Attack speed buff"));
	timedEvents[0]->Pause();
}

void SynergyManager::Update(float deltaTime)
{
	for (TimeEvent* tEvent : timedEvents)
		tEvent->Tick(deltaTime);
}

/// <summary>
/// called by Inventory
/// </summary>
/// <param name="currentlyEquiped"></param>
void SynergyManager::CheckSynergies(std::vector<Item*> currentlyEquiped)
{
	reds = 0;
	blues = 0;
	greens = 0;

	for (Item* item : currentlyEquiped)
	{
		if (item != nullptr)
		{
			switch (*item->GetSynergy())
			{
			case Synergy::blue:
				blues++;
				break;
			case Synergy::green:
				greens++;
				break;
			case Synergy::red:
				reds++;
				if (reds == 2)
					timedEvents[0]->Play();
				if(reds == 3)
					timedEvents[0]->SetInterval(5);
				break;
			default:
				break;
			}
		}
	}
}

void SynergyManager::OnStartLevel(Entity* player)
{
	if(reds >= 2)
		timedEvents[0]->Reset();

	float armourPercentage = 0;
	switch (blues)
	{
	case 1:
		armourPercentage = 0.1f;
		break;
	case 2:
		armourPercentage = 0.2f;
		break;
	case 3:
		armourPercentage = 0.4f;
		break;
	default:
		break;
	}
	playerArmour->SetArmourValue(static_cast<float>(player->GetMaxHealth()) / armourPercentage);

}

void SynergyManager::OnEndLevel()
{
	timedEvents[0]->Pause();
	playerWeapon->AddAttackSpeedMultiplier(-extraAS);
	extraAS = 0;
}

void SynergyManager::OnSuccesfullAttack()
{
	if (greens == 0)
		return;
	int damage = greens - 1;

	for (unsigned int i = 0; i < playerWeapon->GetTargetHits(); i++)
	{
		playerWeapon->AddAttackDamage(damage);
		extraAD += damage;
	}
}


void SynergyManager::PlayerHit()
{
	playerWeapon->AddAttackDamage(-extraAD);
	extraAD = 0;
}

void SynergyManager::AddAttackSpeedBuff()
{
	playerWeapon->AddAttackSpeedMultiplier(10);
	extraAS += 10;
}
