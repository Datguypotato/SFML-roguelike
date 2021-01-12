#include "FanSword.h"

FanSword::FanSword(sf::Texture* itemText, std::string name, SlotRegion* sr)
	:	Item(itemText, name, sr)
{
	damage = 2;
}

FanSword::FanSword(sf::Texture* itemText, std::string name, SlotRegion* sr, Item* upgrade)
	:	 Item(itemText, name, sr, upgrade)
{
	damage = 2;
}

void FanSword::Update(float deltaTime)
{
	for (SlimeBall* projectile : projectiles)
	{
		projectile->Update(deltaTime);
	}
}

void FanSword::Draw(sf::RenderWindow& window)
{
	Item::Draw(window);

	for (SlimeBall* projectile : projectiles)
	{
		projectile->Draw(window);
	}
}

int FanSword::OnAttack(sf::Vector2f startingPos, sf::Vector2f direction)
{
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	//	direction = sf::Vector2f(-1, 0);

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	//	direction = sf::Vector2f(1, 0);

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	//	direction = sf::Vector2f(0, 1);

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	//	direction = sf::Vector2f(0, -1);

	projectiles.push_back(BuildWindSlash(direction, startingPos));
	return 0;
}

std::string FanSword::GetItemStats()
{
	std::string temp = Item::GetItemStats();
	temp += "WindSlash damage: " + std::to_string(damage) + "\n";
	return temp;
}

SlimeBall* FanSword::BuildWindSlash(sf::Vector2f dir, sf::Vector2f startingPos)
{
	std::vector<Animation*> temp = std::vector<Animation*>();
	sf::Texture* texture = new sf::Texture(); 
	texture->loadFromFile("Art/WindSlash.png");
	temp.push_back(new Animation(texture, 1, 1, "Default"));

	SlimeBall* ball = new SlimeBall(temp, dir, damage);
	ball->SetPosition(startingPos);
	projectiles.push_back(ball);

	return ball;
}
