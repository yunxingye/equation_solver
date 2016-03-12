/*
File Name: MapValue.h
Purpose: Header file for class MapValue.h
Author: Gayatri Powar
*/



#pragma once
#include<string>
#include<list>

using namespace std;
class MapValue
{
public:
	//Constructor/Destructor
	MapValue();
	~MapValue();

	//Getter/Setter
	bool getallValuesFound();
	void setallValuesFound(bool valuesFound);
	int getValue();
	void setValue(int writeValue);

	//List to store RHS variables
	list<string> VariableList;

private:
	int value; // Value of RHS
	bool allValuesFound; // bool if all variables are found
};
