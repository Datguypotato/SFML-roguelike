#include "TimeEvent.h"

TimeEvent::TimeEvent(std::function<void()> callback, float interval, bool oneShot, std::string eventName)
{
	this->callback = callback;
	this->interval = interval;
	timer = interval;
	isPaused = false;
	isOneShot = oneShot;

	name = eventName;
}

void TimeEvent::Tick(float deltaTime)
{
	if (!isPaused)
		timer -= deltaTime;

	if (timer <= 0)
	{
		timer = interval - timer;
		if (isOneShot)
			isPaused = true;
		
		callback();
	}
}

void TimeEvent::Play()
{
	isPaused = false;
}

void TimeEvent::Pause()
{
	isPaused = true;
}

void TimeEvent::Reset()
{
	isPaused = false;
	timer = interval;
}
