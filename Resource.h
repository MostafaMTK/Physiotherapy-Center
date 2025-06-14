#pragma once
#include <iostream>
using namespace std;
class Resource
{
protected:
	const int ID;
	char Type;
public:
	Resource(char t, int id);
	virtual ~Resource();
	int GetID() const;
	char GetType() const;
	friend ostream& operator<< (ostream& o, Resource* r);
};
