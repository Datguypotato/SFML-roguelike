#pragma once
#include <functional>

class TimeEvent
{
public:
	TimeEvent(std::function<void()> callback, float interval);
	TimeEvent(std::function<void()> callback, float interval, bool oneShot);

	void Tick(float deltaTime);
	void Play();
	void Pause();
	void Reset();

	float GetTimer() { return timer; }

	void SetInterval(float i) { interval = i; Reset(); }

private:
	float timer;
	bool isPaused;
	bool isOneShot;

	float interval;
	std::function<void()> callback;
};

