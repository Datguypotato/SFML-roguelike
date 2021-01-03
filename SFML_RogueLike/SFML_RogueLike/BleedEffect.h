#pragma once
#include "Effect.h"

class BleedEffect : public Effect
{
public:
	BleedEffect(int amount, int dmg);
	int GetEffect() override;

private:
	int damage;
};

