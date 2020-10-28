#include "AnimatorController.h"
#include <iostream>

// TODO: fill methods
AnimatorController::AnimatorController(std::map<std::string, Animation> animations)
{
	// assign animations
	this->animations = animations;
}
AnimatorController::~AnimatorController()
{
}

void AnimatorController::Play(std::string animationName)
{
	// play animation based on animation name
	for (auto const& anim : animations)
	{
		if (anim.first == animationName)
		{
			activeAnimation = anim.second;
			//std::cout << "Current animation playing: " << activeAnimation.GetAnimationName() << std::endl;
		}
	}
}

void AnimatorController::UpdateAnimation(float deltaTime, bool faceRight)
{
	activeAnimation.Update(0, deltaTime, faceRight);
}