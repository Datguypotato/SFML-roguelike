#include "BleedEffect.h"

BleedEffect::BleedEffect(EffectValue ev)
	:	Effect(ev)
{
}

int BleedEffect::GetEffect()
{
	effectTimes--;
	return effectValue.bleedDamage;
}
