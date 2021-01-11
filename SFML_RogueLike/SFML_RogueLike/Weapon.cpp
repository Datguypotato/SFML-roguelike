#include "Weapon.h"

Weapon::Weapon(int ad, float at)
	:	attackDamage(ad),
		attackTimer(at),
		attackTimerMax(at),
		timesAttacked(0),
		activeitems(std::vector<Item*>())
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
			int extra = 0;
			for (Item* i : activeitems)
			{
				if(i != nullptr)
					extra += i->OnAttack(target);
			}


			target->OnHit(attackDamage + extra);
		}
		inRange.clear();
		//std::cout << "Player has attacked " << timesAttacked << " times\n";
	}

}

void Weapon::Update(float deltaTime)
{
	attackTimer -= deltaTime;
}

void Weapon::UpdateItems(std::vector<Item*> items)
{
	activeitems = items;

	//effectvalue = EffectValue();

	//for (Item* item : items)
	//{
	//	if (item != nullptr)
	//	{
	//		EffectValue temp = item->GetEffectValue();
	//		effectvalue.bleedDamage += temp.bleedDamage;
	//		effectvalue.bleedTimes += temp.bleedTimes;
	//		effectvalue.stunPercentage += temp.stunPercentage;
	//		effectvalue.stunTime += temp.stunTime;
	//	}
	//}
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