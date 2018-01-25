/*
File Name: Graph.h
Description: Header file for class Graph.h
Author: Yunxing Ye
*/
#ifndef GRAPH_H
#define GRAPH_H

#include<string>
#include<fstream>
#include<unordered_map>
#include<unordered_set>
#include<map>

using namespace std;

class Graph
{
public:
    //Constructor
    Graph(ifstream& file, bool isDebug);
    //Destructor
    ~Graph();
    bool calculate();
    void printOutput();
    bool enoughEqus();
    bool invalidEqus();
private:
    bool isInt(const string&  s);
    void initKey(const string& s);
    // maps a vaible name to the variables (name and cofficient) which depend on it 
    unordered_map<string, unordered_map<string, float>> edges;
    unordered_map<string, int> inDegrees;
    // use map so it's sorted by key
    map<string, float> rhsConst;
    int numEquations;  
    bool invalidEquation;
};
#endif   /*GRAPH_H*/
