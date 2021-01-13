#include "EffectHandler.h"

EffectHandler::EffectHandler()
	:	stunTimer(0)
{
	effects = std::vector<Effect*>();
}

void EffectHandler::SetBleed(float time, int damage)
{
	if (time == 0 || damage == 0)
		return;

	EffectValue ev;
	ev.bleedTimes = time;
	ev.bleedDamage = damage;

	effects.push_back(new BleedEffect(ev));
}

void EffectHandler::SetBleed(BleedEffect* bleedEffect)
{
	if (bleedEffect == nullptr || bleedEffect->GetEffect() == 0 || bleedEffect->GetTimes() == 0)
		return;

	effects.push_back(bleedEffect);
}

void EffectHandler::SetStunned(float time)
{
	if (time <= 0)
		return;

	if (stunTimer < time)
		stunTimer = time;

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

bool EffectHandler::IsStunned()
{
	return (stunTimer > 0);
}

void EffectHandler::CountDownStun(float deltaTime)
{
	stunTimer -= deltaTime;
}

