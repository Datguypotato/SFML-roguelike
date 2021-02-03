#include "TimeEvent.h"

/// <summary>
/// if Oneshot = true. The TimeEvent will pause itself after every execution
/// </summary>
/// <param name="callback"></param>
/// <param name="interval"></param>
/// <param name="oneShot"></param>
/// <param name="eventName"></param>
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

/// <summary>
/// Set pause to false
/// </summary>
void TimeEvent::Play()
{
	isPaused = false;
}

/// <summary>
/// set pause to true
/// </summary>
void TimeEvent::Pause()
{
	isPaused = true;
}


/// <summary>
/// set pause to false
/// and reset the timer
/// </summary>
void TimeEvent::Reset()
{
	isPaused = false;
	timer = interval;
}
