#pragma once
#include "Treatment.h"
class Scheduler;
class Patient;
class X_Therapy : public Treatment
{
public:
	X_Therapy(int d);
	virtual bool canAssign(Scheduler* );
	virtual void moveToWait(Scheduler* , Patient*);
	virtual void returnDevice(Scheduler*);
	virtual int GetListLatency(Scheduler*);
};

