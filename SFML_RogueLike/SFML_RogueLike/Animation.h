#pragma once
#include <SFML/Graphics.hpp>

#include <string>
#include <iostream>

class Animation
{
public:
	Animation();
	Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
	Animation(sf::Texture* texture, int imageCount, float switchTime, std::string animationName);
	~Animation();


	void Update(int row, float deltaTime, bool faceRight);
	std::string GetAnimationName() { return animationName; }

	sf::IntRect uvRect;

private:
	sf::Vector2u imageCount;
	sf::Vector2u currentImage;

	float totalTime;
	float switchTime;

	std::string animationName;
};

