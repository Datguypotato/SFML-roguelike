#include "TimeEvent.h"

TimeEvent::TimeEvent(std::function<void()> callback, float interval)
{
	this->callback = callback;
	this->interval = interval;
	timer = interval;
	isPaused = false;
}

void TimeEvent::Tick(float deltaTime)
{
	if (!isPaused)
		timer -= deltaTime;

	if (timer <= 0)
	{
		timer = interval - timer;
		callback();
	}
}

void TimeEvent::Pause(bool p)
{
	isPaused = p;
}

void TimeEvent::Reset()
{
	isPaused = false;
	timer = interval;
}
