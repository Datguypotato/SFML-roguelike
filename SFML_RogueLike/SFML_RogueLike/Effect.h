#pragma once

struct EffectValue
{
	int damage;
	float stunTime;
	float stunPercentage;
	int bleedTimes;
	int bleedDamage;
};

class Effect
{
public:
	Effect(EffectValue ev);

	virtual int GetEffect() { return 0; }

	int GetTimes() { return effectTimes; }
protected:
	int effectTimes;

	EffectValue effectValue;
};
