#include<iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "Scheduler.h"
#include "Patient.h"
using namespace std;

int main()
{
	srand(time(NULL));
	Scheduler s;
	s.Simulation();
	s.exportData();
	return 0;
}