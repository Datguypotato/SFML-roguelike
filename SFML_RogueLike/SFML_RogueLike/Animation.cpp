#include "Animation.h"
Animation::Animation()
	:	switchTime(),
		totalTime(),
		currentImage(),
		imageCount()
{

}
Animation::Animation(sf::Texture* texture, int imageCount, float switchTime)
{
	this->imageCount = imageCount;
	this->switchTime = switchTime;
	totalTime = 0;
	currentImage = 0;

	uvRect.width = texture->getSize().x / float(imageCount);
	uvRect.height = texture->getSize().y;
}

Animation::Animation(sf::Texture* texture, int imageCount, float switchTime, std::string animationName)
	:Animation::Animation(texture, imageCount, switchTime)
{
	this->animationName = animationName;
}

Animation::~Animation()
{
}

// TODO: remove row
void Animation::Update(float deltaTime, bool faceRight)
{
	totalTime += deltaTime;

	if (totalTime >= switchTime)
	{
		totalTime -= switchTime;
		currentImage++;

		if (currentImage >= imageCount)
		{
			currentImage = 0;
		}

		uvRect.top = uvRect.height;

		if (faceRight)
		{
			uvRect.left = currentImage * uvRect.width;
			uvRect.width = abs(uvRect.width);
		}
		else
		{
			uvRect.left = (currentImage + 1) * abs(uvRect.width);
			uvRect.width = -abs(uvRect.width);
		}
	}
}