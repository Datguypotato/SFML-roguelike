#include "ShieldSword.h"

ShieldSword::ShieldSword(sf::Texture* itemText, std::string name)
	:	Shield(itemText, name)
{
	attackDamage = 10;
}

int ShieldSword::OnHit(Entity* entity)
{
	if (isEmpowered)
		return entity->GetAttackDamage() / 2;
	else
		return 0;
}

std::string ShieldSword::GetItemStats()
{
	std::string temp = Shield::GetItemStats();
	temp += "When succesfully blocking a enemy attack\nnext attack is empowered";
	temp += "Empowered attack deal base attack damage + enemy attack damage / 2";
	return temp;
}
