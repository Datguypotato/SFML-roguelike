#pragma once
#include <vector>
#include <string>
#include <animation.h>

class AnimatorController
{
public:
	AnimatorController(std::map<std::string, Animation*> animations);
	~AnimatorController();

	void Play(std::string animationName, bool faceRight);
	void PlayNoInterupt(std::string animationName, bool faceRight);
	void UpdateAnimation(float deltaTime, bool faceRight);

	Animation* GetActiveAnimation() { return activeAnimation; }
	std::string GetCurrentAnimationName() { return activeAnimation->GetName(); }

private:
	std::map<std::string, Animation*> animations;
	Animation* activeAnimation;

	bool uninterruptibleIsPlaying;
};

