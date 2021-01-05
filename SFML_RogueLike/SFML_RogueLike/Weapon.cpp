#include "Weapon.h"

Weapon::Weapon(int ad, float at)
	:	attackDamage(ad),
		attackTimer(at),
		attackTimerMax(at),
		timesAttacked(0),
		effectvalue(EffectValue())
{
	attackbox.setSize(sf::Vector2f(75, 75));
	attackbox.setOrigin(attackbox.getSize() / 2.0f);
	attackbox.setTexture(nullptr);
}

void Weapon::Attack()
{
	if (CanAttack())
	{
		attackTimer = attackTimerMax;
		timesAttacked++;

		for (auto target : inRange)
		{
			target->OnHit(attackDamage);
			
			if (timesAttacked % 3 == 0)
				target->GetEffectHandler()->SetBleed(effectvalue.bleedTimes, effectvalue.bleedDamage);

			if (rand() % 100 < effectvalue.stunPercentage)
				target->GetEffectHandler()->SetStunned(effectvalue.stunTime);
		}
		inRange.clear();
		std::cout << "Player has attacked " << timesAttacked << " times\n";
	}

}

void Weapon::Update(float deltaTime)
{
	attackTimer -= deltaTime;
}

void Weapon::UpdateItems(std::vector<Item*> items)
{
	effectvalue = EffectValue();

	for (Item* item : items)
	{
		if (item != nullptr)
		{
			EffectValue temp = item->GetEffectValue();
			effectvalue.bleedDamage += temp.bleedDamage;
			effectvalue.bleedTimes += temp.bleedTimes;
			effectvalue.stunPercentage += temp.stunPercentage;
			effectvalue.stunTime += temp.stunTime;
		}
	}
}

void Weapon::Draw(sf::RenderWindow& window)
{
	if (CanAttack())
		window.draw(attackbox);
}

Collider Weapon::GetAttackBox()
{
	return Collider(attackbox);
}