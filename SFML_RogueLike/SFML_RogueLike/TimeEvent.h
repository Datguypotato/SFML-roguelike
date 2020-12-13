#pragma once
#include <functional>

class TimeEvent
{
public:
	TimeEvent(std::function<void()> callback, float interval);

	void Tick(float deltaTime);
	void Pause(bool p);
	void Reset();

	float GetTimer() { return timer; }

private:
	float timer;
	bool isPaused;

	float interval;
	std::function<void()> callback;
};

