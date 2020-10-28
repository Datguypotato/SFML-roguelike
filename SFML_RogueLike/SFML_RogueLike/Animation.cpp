#include "Animation.h"
Animation::Animation()
	:	switchTime(),
		totalTime(),
		currentImage(),
		imageCount()
{

}
Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
{
	this->imageCount = imageCount;
	this->switchTime = switchTime;
	totalTime = 0.0f;
	currentImage.x = 0;

	uvRect.width = texture->getSize().x / float(imageCount.x);
	uvRect.height = texture->getSize().y / float(imageCount.y);
}

//Animation::Animation(sf::Texture* texture, sf:: imageCount, float switchTime, std::string animationName)
//	:Animation::Animation(texture, imageCount, switchTime)
//{
//	this->animationName = animationName;
//}

Animation::~Animation()
{
}

// TODO: remove row
void Animation::Update(int row, float deltaTime, bool faceRight)
{
	totalTime += deltaTime;
	currentImage.y;

	if (totalTime >= switchTime)
	{
		totalTime -= switchTime;
		currentImage.x++;

		if (currentImage.x >= imageCount.x)
		{
			currentImage.x = 0;
		}

		uvRect.top = uvRect.height;

		if (faceRight)
		{
			uvRect.left = currentImage.y * uvRect.width;
			uvRect.width = abs(uvRect.width);
		}
		else
		{
			uvRect.left = (currentImage.x + 1) * abs(uvRect.width);
			uvRect.width = -abs(uvRect.width);
		}
	}
}