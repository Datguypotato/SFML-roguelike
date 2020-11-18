#include "Ground.h"

Ground::Ground(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position)
{
	body.setSize(size);
	body.setOrigin(size / 2.0f);
	body.setTexture(texture);
	body.setPosition(position);
}

Ground::Ground(sf::Sprite sprite, sf::Vector2f size, sf::Vector2f position)
{
	body.setSize(size);
	body.setOrigin(size / 2.0f);
	body.setPosition(position);

	sprite.setTextureRect(sf::IntRect(0, 0, size.x, size.y));
	sprite.setOrigin(size / 2.0f);
	sprite.setPosition(position);
	this->sprite = sprite;
}

Ground::~Ground()
{
}

void Ground::Draw(sf::RenderWindow& window)
{
	if(body.getTexture() != NULL)
		window.draw(body);

	if (sprite.getTexture() != NULL)
		window.draw(sprite);
}
