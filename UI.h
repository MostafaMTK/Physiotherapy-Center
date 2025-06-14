#pragma once
#include"LinkedQueue.h"
#include "X_Therapy.h"
#include "EU_WaitList.h"
#include "X_WaitList.h"
#include "ArrayStack.h"
#include "PriQueue.h"
#include "EarlyPList.h"
#include "Resource.h"

class UI
{
public:
	void userinput(int);
	void printDetails(int current_timestep, EU_WaitList* E_WList, EU_WaitList* U_WList, X_WaitList* X_WList, LinkedQueue<Resource*>* E_Devices, LinkedQueue<Resource*>* U_Devices,
		LinkedQueue<Resource*>* X_Rooms, LinkedQueue<Patient*>* AllPatients, ArrayStack<Patient*>* FinishedPatients, EarlyPList* EarlyPatients,
		PriQueue<Patient*>* LatePatients, PriQueue<Patient*>* InTreatmentPatients);
	string getinputfilename();
	string getoutputfilename();
	bool getinterfacemode();
};