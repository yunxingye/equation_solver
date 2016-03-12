/*
File Name: main.cpp
Purpose: cpp file for main
Author: Gayatri Powar
*/


#pragma warning(disable:4996)
#include<iostream>
#include<string>
#include<fstream>
#include<map>
#include"MapValue.h"
using namespace std;


/*
Function Name: CheckAllValueOfMap
Purpose: To check if all RHS are solved. Returns true if all solved
*/
bool CheckAllValueOfMap(map<string, MapValue> &myMap); 

/*
Function Name: Calculate
Purpose: Iterates over the map and solves equations until CheckAllValueOfMap returns true
*/
bool Calculate(map<string, MapValue> &myMap);

/*
Function Name: isInteger
Purpose: Checks if current string is an integer. Returns true if integer.
*/
bool isInteger(const std::string & s);



/*
Function Name: main
Purpose: main execution function
*/
int main(int argc, char** argv)
{
	if (argc != 2)
	{
		cout << "\nPlease enter valid arguments";
		return 0;
	}

	//Map of LHS as key and MapValue Class as value
	map<string, MapValue> EquationMap;
	
	string filePath = argv[1];
	ifstream file;
	file.open(filePath);
	if (!file.is_open())
	{
		cout << "\n File not opened";
		return 0;
	}
	string temp;
	string line;
	bool isKey = true;
	while (getline(file, line))
	{
		char * cstr = new char[line.length() + 1];
		strncpy(cstr,  line.c_str(), line.length() + 1);

		char *pch = strtok(cstr, " =+");
		MapValue mapvalue;
		string key;
		bool allNum = true;
		int valueofList = 0;
		while (pch != NULL)
		{
		    //First string is LHS  and is stored as key
			if (isKey == true)
			{
				key = pch;
				isKey = false;
			}
			else
			{
				//Create List of strings to store in MapValue class. 
				//To be used as Value of respective key
				bool isNum = isInteger(pch);
				mapvalue.VariableList.push_back(pch);
				if (!isNum)
				{
					allNum = false;
				}
				else
				{
					valueofList = valueofList + stoi(pch);
				}
			}
			pch = strtok(NULL, " =+");
		}
		//allNum indicates all the variables are integers and RHS is solved
		mapvalue.setallValuesFound(allNum);
		//valueoflist is current value of all integers in list.
		mapvalue.setValue(valueofList);
		//Insert the value in sorted map for key
		EquationMap.insert({ key, mapvalue });

		isKey = true;
		
	}
	file.close();
	
	bool result = Calculate(EquationMap);
	
	//Print all the key value pairs
	map<string, MapValue>::iterator it;
	for (it = EquationMap.begin(); it != EquationMap.end(); it++)
	{
		cout << it->first << " = " << it->second.getValue() << "\n";
	}
	
	return 0;
}


bool CheckAllValueOfMap(map<string, MapValue> &myMap)
{
	map<string, MapValue>::iterator it;
	for (it = myMap.begin(); it != myMap.end(); it++)
	{
		if (it->second.getallValuesFound() == false)
			return false;
	}
	return true;
}


bool Calculate(map<string, MapValue> &myMap)
{
	/*
	Psedo Code:
	while(!All RHS solved)
	{
	  for each key 
	  {
	      bool solved = true;
	      for each Value->list<string>
		  {
		    if(!isNumber(string)
			{ solved = false ; break;} 
		  }

		  if(solved == true)
		  {
		   Calculate final value of RHS
		   Set Final Value in Map
		  }
	  }
	  return true when solved
	}
	
	*/
	map<string, MapValue>::iterator it;
	while (!CheckAllValueOfMap(myMap))
	{
		for (it = myMap.begin(); it != myMap.end(); it++)
		{
			if (it->second.getallValuesFound() == false)
			{
				list<string>::iterator strit;
				bool listover = true;
				for (strit = it->second.VariableList.begin(); strit != it->second.VariableList.end(); strit++)
				{
					bool isCurrInt = isInteger(*strit);
					if (!isCurrInt)
					{
						map<string, MapValue>::iterator pos = myMap.find(*strit);
						if (pos != myMap.end())
						{
							if (pos->second.getallValuesFound())
							{
								*strit = to_string(pos->second.getValue());
							}
							else
							{
								listover = false;
								break;
							}
						}
					}
				}
				if (listover)
				{
					list<string>::iterator finalListIt;
					unsigned int finalVal = 0;
					for (finalListIt = it->second.VariableList.begin(); finalListIt != it->second.VariableList.end(); finalListIt++)
					{

						finalVal += stoi(*finalListIt);

					}
					it->second.setValue(finalVal);
					it->second.setallValuesFound(true);
				}
			}
		}
	}
	return true;
}

bool isInteger(const std::string & s)
{
	if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;

	char * p;
	strtol(s.c_str(), &p, 10);
	return (*p == 0);
}