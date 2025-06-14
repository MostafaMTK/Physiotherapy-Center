#include "UI.h"

void UI::userinput(int current_timestep)
{
	cout << "Press Enter to display next timestep";
	if (current_timestep == 1)
		cin.ignore();
	cin.get();
}

void UI::printDetails(int current_timestep, EU_WaitList* E_WList, EU_WaitList* U_WList, X_WaitList* X_WList, LinkedQueue<Resource*>* E_Devices, LinkedQueue<Resource*>* U_Devices,
	LinkedQueue<Resource*>* X_Rooms, LinkedQueue<Patient*>* AllPatients, ArrayStack<Patient*>* FinishedPatients, EarlyPList* EarlyPatients,
	PriQueue<Patient*>* LatePatients, PriQueue<Patient*>* InTreatmentPatients)
{
	cout << endl << "Current timestep: " << current_timestep << endl;
	cout << "===============  ALL List  =============== " << endl
		<< AllPatients->GetCount() << " patients remaining: ";
	AllPatients->Print(10);
	cout << endl;
	cout << "===============  Waiting Lists  =============== " << endl;
	cout << E_WList->GetCount() << " E-therapy patients: ";
	E_WList->Print();
	cout << endl;
	cout << U_WList->GetCount() << " U-therapy patients: ";
	U_WList->Print();
	cout << endl;
	cout << X_WList->GetCount() << " X-therapy patients: ";
	X_WList->Print();
	cout << endl;
	cout << "===============  Early List  =============== " << endl
		<< EarlyPatients->GetCount() << " patients: ";
	EarlyPatients->Print();
	cout << endl;
	cout << "===============  Late List  =============== " << endl
		<< LatePatients->GetCount() << " patients: ";
	LatePatients->Print();
	cout << endl;
	cout << "===============  Avail E-devices  =============== " << endl
		<< E_Devices->GetCount() << " Elctro device: ";
	E_Devices->Print();
	cout << endl;
	cout << "===============  Avail U-devices  =============== " << endl
		<< U_Devices->GetCount() << " Ultra device: ";
	U_Devices->Print();
	cout << endl;
	cout << "===============  Avail X-rooms  =============== " << endl
		<< X_Rooms->GetCount() << " rooms: ";
	X_Rooms->Print();
	cout << endl;
	cout << "===============  In-treatment List  =============== " << endl
		<< InTreatmentPatients->GetCount() << " ==> ";
	InTreatmentPatients->Print();
	cout << endl;
	cout << "---------------------------------------" << endl <<
		FinishedPatients->GetCount() << " finished patients: ";
	FinishedPatients->Print();
	cout << endl;
	userinput(current_timestep);
}

string UI::getinputfilename()
{
	cout << "Enter input file name (Please match the file name exactly) : ";
	string inputfilename;
	cin >> inputfilename;
	return inputfilename;
}

string UI::getoutputfilename()
{
	cout << "Enter output file name : ";
	string outputfilename;
	cin >> outputfilename;
	return outputfilename;
}

bool UI::getinterfacemode()
{
	cout << "Choose the mode you want \n 1)Silent Mode		2)Interactive Mode		: ";
	int x;
	cin >> x;
	return (x-1);
}
