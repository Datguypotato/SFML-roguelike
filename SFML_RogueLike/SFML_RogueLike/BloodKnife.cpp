#include "BloodKnife.h"

BloodKnife::BloodKnife(sf::Texture* itemText, std::string name)
	:	Knife(itemText, name)
{
}

int BloodKnife::OnHit(Entity* entity)
{
	if (attacks % 3 == 0)
	{
		entity->GetEffectHandler()->SetBleed(bleedTimes, bleedDamage);
		return extraDamage;
	}
		
	return 0;
}

std::string BloodKnife::GetItemStats()
{
	std::string temp = Knife::GetItemStats();
	temp += "Bleed time: " + std::to_string(bleedTimes) + "x\n" +
			"Bleed damage: " + std::to_string(bleedDamage) + "\n";
	return temp;
}
