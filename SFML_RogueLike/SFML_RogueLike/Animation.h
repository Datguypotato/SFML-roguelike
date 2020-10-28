#pragma once
#include <SFML/Graphics.hpp>

#include <string>

class Animation
{
public:
	Animation();
	Animation(sf::Texture* texture, int imageCount, float switchTime);
	Animation(sf::Texture* texture, int imageCount, float switchTime, std::string animationName);
	~Animation();


	void Update(float deltaTime, bool faceRight);
	std::string GetAnimationName() { return animationName; }

	sf::IntRect uvRect;

private:
	int imageCount;
	int currentImage;

	float totalTime;
	float switchTime;

	std::string animationName;
};

