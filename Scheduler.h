#pragma once
#include "EU_WaitList.h"
#include "X_WaitList.h"
#include "ArrayStack.h"
#include "PriQueue.h"
#include "EarlyPList.h"
#include <string>
#include "UI.h"
class Patient;
class Treatment;
class Resource;
class Scheduler
{
	int CurrentTimeStep;
	EU_WaitList E_WList;
	EU_WaitList U_WList;
	X_WaitList X_WList;
	LinkedQueue<Resource*> E_Devices;
	LinkedQueue<Resource*> U_Devices;
	LinkedQueue<Resource*> X_Rooms;
	LinkedQueue<Patient*> AllPatients;
	ArrayStack<Patient*> FinishedPatients;
	EarlyPList EarlyPatients;
	PriQueue<Patient*> LatePatients;
	PriQueue<Patient*> InTreatmentPatients;
	int NumOfAllPatients;
	int NumOfNP;
	int NumOfRP;
	int NumOfEarlyP;
	int NumOfLateP;
	int TotalWaitingNP;
	int TotalWaitingRP;
	int TotalTreatmentNP;
	int TotalTreatmentRP;
	int TotalPenalties;
	int NumOfCancels;
	int NumOfResc;
	int NE;
	int NU;
	int NG;
	int PCancel;
	int PResc;
	string inputfilename;
	string outputfilename;
	bool interfacemode;
	UI userinterface;
public:
	Scheduler();
	int GetCurrentTimeStep() const;
	void moveToE_Waiting(Patient* p);
	void moveToU_Waiting(Patient* p);
	void moveToX_Waiting(Patient* p);
	Patient* getNextE_Patient();
	Patient* getNextU_Patient();
	Patient* getNextX_Patient();
	Patient* getNextALL_Patient();
	Resource* getE_Device();
	Resource* getU_Device();
	Resource* getX_Room();
	void retrieveE_Device(Resource* r);
	void retrieveU_Device(Resource* r);
	void retrieveX_Room(Resource* r);
	void moveToEarlyPatients(Patient* p);
	void moveToLatePatients(Patient* p);
	void moveToInTreatmentPatients(Patient* p);
	void moveToFinishedPatients(Patient* p);
	bool isAvailableE_Device();
	bool isAvailableU_Device();
	bool isAvailableX_Room();
	int getE_Latency();
	int getU_Latency();
	int getX_Latency();
	void importData();
	void exportData();
	void printDetails(int X);
	void move1TimeStep();
	void Simulation();
	~Scheduler();
};

