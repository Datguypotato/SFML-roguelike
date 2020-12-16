#include "TimeEvent.h"

TimeEvent::TimeEvent(std::function<void()> callback, float interval)
{
	this->callback = callback;
	this->interval = interval;
	timer = interval;
	isPaused = false;
	isOneShot = false;
}

/// <summary>
/// setting onshot to true will pause the TimeEvent after each completion
/// </summary>
/// <param name="callback"></param>
/// <param name="interval"></param>
/// <param name="oneShot"></param>
TimeEvent::TimeEvent(std::function<void()> callback, float interval, bool oneShot)
	:	TimeEvent::TimeEvent(callback, interval)
{
	isOneShot = oneShot;
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
