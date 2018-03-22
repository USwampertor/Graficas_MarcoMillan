#ifndef T800_TIMER_H
#define T800_TIMER_H
#include <windows.h>


//#include <sys/time.h>

class Timer {
public:
	void Init();
	void Update();

	float	GetDTSecs();


	LARGE_INTEGER	StartTime;

	//timeval	        StartTime;

	double			Frequency;
	double			Dt;
	double			DtSecs;
};

#endif
#pragma once
