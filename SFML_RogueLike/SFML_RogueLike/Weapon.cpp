#include "Weapon.h"

Weapon::Weapon(int ad, float at)
	:	attackDamage(ad),
		attackTimer(at),
		baseAttackDamage(ad),
		baseAttackTimerMax(at),
		attackTimerMax(at),
		timesAttacked(0),
		activeWeapon(nullptr),
		recentDead(0)
{
	attackbox.setSize(sf::Vector2f(75, 75));
	attackbox.setOrigin(attackbox.getSize() / 2.0f);
	attackbox.setTexture(nullptr);
}

void Weapon::Attack(sf::Vector2f startingPos, sf::Vector2f facingDir)
{
	if (CanAttack())
	{
		attackTimer = attackTimerMax;
		timesAttacked++;

		if (activeWeapon != nullptr)
			activeWeapon->OnAttack(startingPos, facingDir);

		for (Entity* target : inRange)
		{
			int extra = 0;
			if (activeWeapon != nullptr)
				extra += activeWeapon->OnHit(target);


			target->OnHit(attackDamage + extra);

			if (!target->GetAliveStatus())
				recentDead++;
		}

		inRange.clear();
		//std::cout << "Player has attacked " << timesAttacked << " times\n";
	}
}

void Weapon::Update(float deltaTime)
{
	attackTimer -= deltaTime;

	if (activeWeapon != nullptr)
	{
		activeWeapon->Update(deltaTime);
		weaponProjectiles = activeWeapon->GetProjectiles();
	}
		
}

void Weapon::SetWeapon(Item* item)
{
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
	if (CanAttack())
		window.draw(attackbox);

	for (Entity* projectiles : weaponProjectiles)
		projectiles->Draw(window);
}

Collider Weapon::GetAttackBox()
{
	return Collider(attackbox);
}

void Weapon::CheckCollision(std::vector<Entity*> enemies)
{
	if (activeWeapon != nullptr)
	{
		for(Entity* e : enemies)
			activeWeapon->CheckCollision(e);
	}
		
}

int Weapon::GetRecentDead()
{
	int temp = recentDead;
	recentDead = 0;
	return temp;
}

