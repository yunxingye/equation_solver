/*
File Name: Map.cpp
Purpose: cpp file for class MapValue
Author: Gayatri Powar
*/

#include"MapValue.h"
#include<map>
#include<string>

using namespace std;
MapValue::MapValue()
{
	value = -1;
	allValuesFound = false;
}

MapValue::~MapValue()
{
}

bool MapValue::getallValuesFound()
{
	return allValuesFound;
	;
}
void MapValue::setallValuesFound(bool valuesFound)
{
	allValuesFound = valuesFound;
}

int MapValue::getValue()
{
	return value;
}
void MapValue::setValue(int writeValue)
{
	value = writeValue;
}

