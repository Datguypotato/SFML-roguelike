#include "EffectHandler.h"

EffectHandler::EffectHandler()
{
	effects = std::vector<Effect*>();
}

void EffectHandler::SetBleed(float time, int damage)
{
	effects.push_back(new BleedEffect(time, damage));
}

void EffectHandler::SetStunned(float time)
{
	if (stunEffect->GetTimes() < time)
		delete stunEffect;
	if (stunEffect == nullptr)
	{
		stunEffect = new StunEffect(time);
	}
}

int EffectHandler::GetBleedDamage()
{
	int totalDamage = 0;
	int index = 0;
	std::vector<int> indexToDelete;
	for (Effect* ef : effects)
	{
		totalDamage += ef->GetEffect();

		if(ef->GetTimes() == 0)
			indexToDelete.push_back(index);
		index++;
	}

	for (int i : indexToDelete)
		effects.erase(effects.begin() + i);

	return totalDamage;
}
