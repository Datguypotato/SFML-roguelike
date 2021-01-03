#pragma once

class Effect
{
public:
	Effect(int et);

	virtual int GetEffect() { return 0; }

	int GetTimes() { return effectTimes; }
protected:
	int effectTimes;
};

