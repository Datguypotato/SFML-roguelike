#include "Weapon.h"

Weapon::Weapon(int ad, float at, AnimatorController a)
	:	attackDamage(ad),
		attackTimer(at),
		baseAttackDamage(ad), // = 1
		baseAttackTimerMax(at), // = 2.5f
		attackTimerMax(at),
		timesAttacked(0),
		activeWeapon(nullptr),
		recentDead(0),
		attackSpeedMultiplier(0),
		targetsHit(0),
		AC(a)
{
	attackbox.setSize(sf::Vector2f(75, 75));
	attackbox.setOrigin(attackbox.getSize() / 2.0f);
	attackbox.setTexture(nullptr);

	attackbox.setTexture(AC.GetActiveAnimation()->GetTexture());
}

void Weapon::Attack(sf::Vector2f startingPos, sf::Vector2f facingDir)
{
	if (CanAttack())
	{
		AC.Play("Attack", true);
		animationCooldown = AC.GetActiveAnimation()->GetAnimationTime();

		attackTimer = attackTimerMax - (attackTimerMax * attackSpeedMultiplier);
		timesAttacked++;

		if (activeWeapon != nullptr)
			activeWeapon->OnAttack(startingPos, facingDir);

		for (Entity* target : inRange)
		{
			int extra = 0;
			if (activeWeapon != nullptr)
			{
				extra += activeWeapon->OnHit(target);
				targetsHit++;
			}

			target->OnHit(attackDamage + extra);

			if (!target->GetAliveStatus())
				recentDead++;
		}
	}
}

void Weapon::Update(float deltaTime)
{
	attackTimer -= deltaTime;
	AC.UpdateAnimation(deltaTime, false);

	if (activeWeapon != nullptr)
	{
		activeWeapon->Update(deltaTime);
		weaponProjectiles = activeWeapon->GetProjectiles();
	}

	animationCooldown -= deltaTime;
	if (animationCooldown <= 0)
		AC.Play("Default", true);

	attackbox.setTexture(AC.GetActiveAnimation()->GetTexture());
	attackbox.setTextureRect(AC.GetActiveAnimation()->uvRect);

}

void Weapon::SetWeapon(Item* item)
{
	if (item == nullptr)
		return;

	if (WeaponItem* w = dynamic_cast<WeaponItem*>(item))
	{
		activeWeapon = static_cast<WeaponItem*>(item);
		attackDamage = baseAttackDamage + activeWeapon->GetAttackDamage();
		attackTimerMax = baseAttackTimerMax - activeWeapon->GetAttackTimerMax();
	}
	else
		activeWeapon = nullptr;

	//activeWeapon = (WeaponItem)items[0];
}

void Weapon::Draw(sf::RenderWindow& window)
{
	window.draw(attackbox);


	for (Entity* projectiles : weaponProjectiles)
		projectiles->Draw(window);
}

void Weapon::OnHit(int dmg)
{
	if (activeWeapon != nullptr)
	{
		if (activeWeapon->GetBlock())
		{
			dmg /= 2;
			activeWeapon->SetEmpowerAttack(true);
			activeWeapon->SetBlock(false);
			std::cout << "Empowered attack " << activeWeapon->GetEmpowerAttack() << "\n";
		}
	}
}

Collider Weapon::GetAttackBox()
{
	return Collider(attackbox);
}

void Weapon::CheckCollision(std::vector<Entity*> enemies)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && CanAttack())
	{
		for (Entity* enemy : enemies)
		{
			Collider eColl = enemy->GetCollider();
			if (GetAttackBox().CheckTrigger(eColl))
				inRange.push_back(enemy);
		}
	}

	if (activeWeapon != nullptr)
	{
		for(Entity* e : enemies)
			activeWeapon->CheckCollision(e);
	}
}

/// <summary>
/// Add percentage attackspeedmultiplioer
/// if percentage is higer then 100 or lower then 0 it will return
/// </summary>
/// <param name="percentage"></param>
void Weapon::AddAttackSpeedMultiplier(int percentage)
{
	if (this != NULL)
	{
		if (percentage < 0 || percentage > 100)
			return;

		attackSpeedMultiplier += static_cast<float>(percentage) / 100;
	}
}

int Weapon::GetRecentDead()
{
	int temp = recentDead;
	recentDead = 0;
	return temp;
}

int Weapon::GetTargetHits()
{
	int temp = targetsHit;
	targetsHit = 0;
	return temp;
}