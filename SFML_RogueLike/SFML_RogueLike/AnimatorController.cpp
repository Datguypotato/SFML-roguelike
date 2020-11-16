#include "AnimatorController.h"
#include <iostream>

// TODO: fill methods
AnimatorController::AnimatorController(std::vector<Animation*> animations)
{
	// assign animations
	this->animations = animations;
	activeAnimation = animations[0];
}
AnimatorController::~AnimatorController()
{
}

AnimatorController::AnimatorController(const AnimatorController& rhs)
{
	animations = rhs.animations;
	activeAnimation = animations[0];

	uninterruptibleIsPlaying = rhs.uninterruptibleIsPlaying;
}

AnimatorController* AnimatorController::Clone() const
{
	return new AnimatorController(*this);
}

void AnimatorController::Play(std::string animationName, bool faceRight)
{
	if (!uninterruptibleIsPlaying)
	{
		// play animation based on animation name
		for (auto const& anim : animations)
		{
			if (anim->GetName() == animationName)
			{
				if (activeAnimation->GetName() != animationName)
				{
					activeAnimation = anim;
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