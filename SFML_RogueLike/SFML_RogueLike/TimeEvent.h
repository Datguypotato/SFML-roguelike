#pragma once
#include <functional>

class TimeEvent
{
public:
	TimeEvent(std::function<void()> callback, float interval, bool oneShot, std::string eventName);

	void Tick(float deltaTime);
	void Play();
	void Pause();
	void Reset();

	void SetInterval(float i) { interval = i; Reset(); }

	float GetTimer() { return timer; }
	std::string GetEventName() { return name; }

private:
	std::string name;

	float timer;
	bool isPaused;
	bool isOneShot;

	float interval;
	std::function<void()> callback;
};

