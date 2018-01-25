/*
File Name: main.cpp
Description: cpp file for main
Author: Yunxing Ye 
*/

#include<iostream>
#include<fstream>
#include<string>
#include"Graph.h"
using namespace std;

#define DEBUG 1

#ifdef DEBUG
#define DEBUG_MSG(str) do { std::cout << str; } while( false )
#else
#define DEBUG_MSG(str) do { } while ( false )
#endif
/*
Function Name: printFile
Description: funciton to print the file when no valid solution
*/
void printFile(ifstream& file);
/*
Function Name: main
Description: The main function
*/

int main(int argc, char** argv)
{
    if(argc != 2)
    {
        cout <<"Please use this program as EquationSolver --path to input file.\n";
        return 0;
    }

    string fpath = argv[1];
    ifstream file;
    file.open(fpath);
    if(!file.is_open())
    {
        DEBUG_MSG("Couldn't open input file.\n");
        return 0;
    }
    bool isDebugMode = false;
#ifdef DEBUG
    isDebugMode = true;
#endif
    Graph G(file,isDebugMode);
    file.clear();
    file.seekg(0, ios::beg);
    if(!G.enoughEqus())
    {
        // not enough equations, there's no solution for all the variables
        DEBUG_MSG("There's no solution(not enough equations)."<<endl);
        printFile(file);
        file.close();
        return 0;
    }

    if(G.invalidEqus())
    {
        // there's invalid equations, lhs variable got canceled out
        DEBUG_MSG("There's no solution(invalid equations,undefined value for the variable)."<<endl);
        printFile(file);
        file.close();
        return 0;
    }

    if(G.calculate())
    {
        G.printOutput();
    }else
    {
        printFile(file);
    }
    file.close();
    return 0;
}


void printFile(ifstream& file)
{
    string line;
    while(getline(file, line))
    {
        cout << line << endl;
    }
}
