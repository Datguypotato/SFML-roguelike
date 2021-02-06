#include "PlatedArmour.h"

PlatedArmour::PlatedArmour(sf::Texture* itemText, std::string name)
	:	KevlarVest(itemText, name)
{
	explosionBox = sf::RectangleShape(sf::Vector2f(range, range));
	explosionBox.setOrigin(range / 2, range / 2);
}

void PlatedArmour::OnExplodeShield(sf::Vector2f playerPos)
{
	explosionBox.setPosition(playerPos);
	isExploded = true;
}

void PlatedArmour::CheckCollision(std::vector<Entity*> entities)
{
	if (isExploded)
	{
		for (Entity* e : entities)
		{
			Collider eColl = e->GetCollider();
			if (Collider(explosionBox).CheckTrigger(eColl))
			{
				e->OnHit(explosionDamage);
			}
		}
		isExploded = false;
	}
}

std::string PlatedArmour::GetItemStats()
{
	return KevlarVest::GetItemStats() + "Once armour is completly destory deal " + std::to_string(explosionDamage) + " damage\n";
}



/// <summary>
/// Used to maybe make a circle collision
/// might revisit in the future
/// </summary>
/// <param name="a"></param>
/// <param name="b"></param>
/// <returns></returns>
float PlatedArmour::Distance(sf::Vector2f a, sf::Vector2f b)
{
	float x = a.x - b.x;
	float y = a.y - b.y;
	return sqrt((x * x) + (y * y));
}
