#pragma once
#include "Effect.h"

class BleedEffect : public Effect
{
public:
	BleedEffect(EffectValue ev);
	int GetEffect() override;

private:
	int damage;
};

