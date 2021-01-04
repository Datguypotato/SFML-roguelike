#pragma once
#include <vector>
#include <iostream>

#include "Effect.h"
#include "BleedEffect.h"

class EffectHandler
{
public:
	EffectHandler();

	void SetBleed(float time, int damage);
	void SetBleed(BleedEffect* bleedEffect);
	void SetStunned(float time);

	int GetBleedDamage();
	bool IsStunned();
	void CountDownStun(float deltaTime);

	bool hasEffects() { return (effects.size() > 0); }

private:
	std::vector<Effect*> effects;
	float stunTimer;
};

