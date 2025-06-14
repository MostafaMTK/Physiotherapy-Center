#pragma once
#include "Treatment.h"
class Scheduler;
class Patient;
class U_Therapy : public Treatment
{
public:
	U_Therapy(int d);
	virtual bool canAssign(Scheduler*);
	virtual void moveToWait(Scheduler*,Patient* );
	virtual void returnDevice(Scheduler*);
	virtual int GetListLatency(Scheduler*);
};

