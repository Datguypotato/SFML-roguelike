#include "Animation.h"

Animation::Animation(sf::Texture* texture, int imageCount, float switchTime)
	:loopedOnce(false)
{
	this->texture = texture;
	this->imageCount = imageCount;
	this->switchTime = switchTime;
	totalTime = 0.0f;
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

Animation* Animation::Clone() const
{
	return new Animation(*this);
}

Animation::Animation(const Animation& rhs)
{
	texture = rhs.texture;
	imageCount = rhs.imageCount;
	switchTime = rhs.switchTime;
	totalTime = rhs.totalTime;
	currentImage = rhs.currentImage;
	uvRect = sf::IntRect();
	loopedOnce = rhs.loopedOnce;

}

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
			loopedOnce = true;
		}

		uvRect.top = 0;//currentImage.y * uvRect.height;

		UpdateFaceingDirection(faceRight);
	}
}
void Animation::UpdateFaceingDirection(bool faceRight)
{
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