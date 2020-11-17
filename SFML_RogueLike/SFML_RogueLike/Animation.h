#pragma once
#include <SFML/Graphics.hpp>

#include <string>
#include <iostream>

class Animation
{
public:
	Animation(sf::Texture* texture, int imageCount, float switchTime, std::string animationName);
	//Animation(const Animation& rhs);
	~Animation();

	Animation* Clone() const;
	void Update(float deltaTime, bool faceRight);
	std::string GetName() { return animationName; }
	void SetName(std::string newName) { animationName = newName; }

	sf::IntRect uvRect;
	sf::Texture* GetTexture() { return texture; }

	bool GetLoopedOnce() { return loopedOnce; }

	void UpdateFaceingDirection(bool faceRight);
private:
	sf::Texture* texture;

	int imageCount;
	int currentImage;

	float totalTime;
	float switchTime;

	std::string animationName;
	bool loopedOnce;
};

