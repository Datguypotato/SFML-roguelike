#include "BleedEffect.h"

BleedEffect::BleedEffect(int amount, int dmg)
	:	Effect(amount),
		damage(dmg)
{
}

int BleedEffect::GetEffect()
{
	effectTimes--;
	return damage;
}
