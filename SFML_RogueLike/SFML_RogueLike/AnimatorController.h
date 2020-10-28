#pragma once
#include <vector>
#include <string>
#include <animation.h>

class AnimatorController
{
public:
	AnimatorController(std::map<std::string, Animation> animations);
	~AnimatorController();

	void Play(std::string animationName);
	void UpdateAnimation(float deltaTime, bool faceRight);
	Animation GetActiveAnimation() { return activeAnimation; }

private:
	std::map<std::string, Animation> animations;
	Animation activeAnimation;
};

