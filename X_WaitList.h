#pragma once
#include "EU_WaitList.h"
class X_WaitList : public EU_WaitList
{
private:

public:
	bool cancel(int Pcancel , Patient* &p);
};

