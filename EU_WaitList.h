#pragma once
#include "LinkedQueue.h"
class Patient;
class EU_WaitList : public LinkedQueue<Patient*>
{
protected:
	int Ttime;
public:
	EU_WaitList();
	void insertSorted(Patient*& newPatient);
	bool enqueue(Patient*& newPatient);
	bool dequeue(Patient*& frntEntry);
	int calcTreatmentLatency() const;
};