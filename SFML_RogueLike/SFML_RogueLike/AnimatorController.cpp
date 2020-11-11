#include "AnimatorController.h"
#include <iostream>

// TODO: fill methods
AnimatorController::AnimatorController(std::map<std::string, Animation*> animations)
{
	// assign animations
	this->animations = animations;
	activeAnimation = animations.begin()->second;
}
AnimatorController::~AnimatorController()
{
}

AnimatorController::AnimatorController(const AnimatorController& rhs)
{
	animations = rhs.animations;
	activeAnimation = animations.begin()->second;
}

void AnimatorController::Play(std::string animationName, bool faceRight)
{
	if (!uninterruptibleIsPlaying)
	{
		// play animation based on animation name
		for (auto const& anim : animations)
		{
			if (anim.first == animationName)
			{
				if (activeAnimation->GetName() != animationName)
				{
					activeAnimation->SetName(animationName);
					activeAnimation = anim.second;
					activeAnimation->UpdateFaceingDirection(faceRight);
				}

			}
		}
	}
}

void AnimatorController::PlayNoInterupt(std::string animationName, bool faceRight)
{
	Play(animationName, faceRight);
	uninterruptibleIsPlaying = true;
}

void AnimatorController::UpdateAnimation(float deltaTime, bool faceRight)
{
	activeAnimation->Update(deltaTime, faceRight);

	if (activeAnimation->GetLoopedOnce())
		uninterruptibleIsPlaying = false;
}