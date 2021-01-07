#include "Item.h"

Item::Item(sf::Texture* itemText)
	:	itemBox(sf::Vector2f(100, 100)),
		itemName("Default"),
		slotRegion(new SlotRegion(SlotRegion::none))
{
	itemBox.setTexture(itemText);
	itemBox.setOrigin(itemBox.getSize() / 2.0f);

	effectValue = EffectValue();
}

Item::Item(sf::Texture* itemText, std::string name)
	:	itemBox(sf::Vector2f(100, 100)),
		itemName(name),
		slotRegion(new SlotRegion(SlotRegion::none))
{
	itemBox.setTexture(itemText);
	itemBox.setOrigin(itemBox.getSize() / 2.0f);
	effectValue = EffectValue();
}

Item::Item(sf::Texture* itemText, std::string name, EffectValue e, SlotRegion* sr)
	:	effectValue(e),
		itemBox(sf::Vector2f(100, 100)),
		itemName(name),
		slotRegion(new SlotRegion(*sr))
{
	itemBox.setTexture(itemText);
	itemBox.setOrigin(itemBox.getSize() / 2.0f);
}

Item::~Item()
{
}

void Item::SetPosition(sf::Vector2f pos)
{
	itemBox.setPosition(pos);
}

void Item::Draw(sf::RenderWindow& window)
{
	window.draw(itemBox);
}

std::string Item::GetItemStats()
{	
	std::string temp = "";
	temp += "bleedDamage: " + std::to_string(effectValue.bleedDamage) + "\n";
	temp += "Bleed time: " + std::to_string(effectValue.bleedTimes) + "\n";
	temp += "stun%: " + std::to_string(effectValue.stunPercentage) + "%\n";
	temp += "stun Time: " + std::to_string(effectValue.stunTime) + "\n";
	return temp;
}
