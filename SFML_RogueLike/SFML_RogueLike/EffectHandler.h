#pragma once
#include <vector>

#include "Effect.h"
#include "BleedEffect.h"
#include "StunEffect.h"

class EffectHandler
{
public:
	EffectHandler();

	void SetBleed(float time, int damage);
	void SetStunned(float time);

	int GetBleedDamage();
	bool IsStunned() { return stunned; }

	bool hasEffects() { return (effects.size() > 0); }

private:
	std::vector<Effect*> effects;
	StunEffect* stunEffect;
	bool stunned;
};

