/*
File Name: Graph.cpp
Description: implentation file for class Graph
Author: Yunxing Ye
*/

#include"Graph.h"
#include<vector>
#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<queue>

using namespace std;

Graph::Graph(ifstream& file, bool isDebug):numEquations(0),invalidEquation(false)
{
    string line;
    while(getline(file, line))
    {
        string lhs;
        int rhsVal = 0;
        char* lineCstr = new char[line.size()+1];
        strncpy(lineCstr, line.c_str(), line.size()+1);
        // get the first token, which is the lhs variable
        char* token = strtok(lineCstr, "=+ ");
        lhs = token;
        initKey(lhs);
        unordered_set<string> rhsVars;
        while(true)
        {
            token = strtok(NULL, "=+ ");
            if(token==NULL)
            {
                break;
            }
            if(isInt(token))
            {
                rhsVal += stoi(token);
            }else
            {
                initKey(token);
                string rs = token;
                if(rs!=lhs && !rhsVars.count(rs))
                {
                    inDegrees[lhs]++;
                }
                rhsVars.insert(rs);
                edges[rs][lhs]++;
            }
        }
        if(rhsVars.empty())
        {
            finalAnswer[lhs] = rhsVal;
        }

        // handle the case when the lhs varibal also appears on the rhs
        if(edges[lhs].count(lhs))
        {
            if(edges[lhs][lhs]==1)
            {
                // there would be infinite solutions for the lhs varible 
                invalidEquation = true;
            }else
            {
                float coff = (float)1.0 - edges[lhs][lhs];
                for(const string& s:rhsVars)
                {
                    edges[s][lhs] /=coff;
                }
                rhsVal /=coff;
            }
            edges[lhs].erase(lhs);
        }
        rhsConst[lhs] = rhsVal;
        delete lineCstr;
        numEquations++;
    }
    if(isDebug)
    {
        cout<<"\nIndegree Map\n";
        for (auto itr = inDegrees.begin(); itr != inDegrees.end(); itr++)
        {
            cout <<itr->first << "  " << itr->second << endl;
        }
        cout<<"\nedge Map\n";
        for (auto itr = edges.begin(); itr != edges.end(); itr++)
        {
            cout<<itr->first << ":";
            for(auto it = itr->second.begin(); it!=itr->second.end(); it++)
            {
                cout << it->first<<" "<<it->second;
            }
            cout<<endl;
        }
        cout<<"\nRight hand side total constant value Map\n";
        for (auto itr = rhsConst.begin(); itr != rhsConst.end(); itr++)
        {
            cout<<itr->first << "  " << itr->second << endl;
        }
        cout << endl;
    }
}

Graph::~Graph()
{
}

bool Graph::calculate()
{
    queue<string> q;
    int n = inDegrees.size();
    for(auto item:inDegrees)
    {
        if(item.second==0)
        {
            q.push(item.first);
            n--;
        }
    }

    while(!q.empty())
    {
        string cur = q.front();
        float curVal = rhsConst[cur];
        q.pop();
        //for(const string& neighbor: edges[cur].first)
        for(auto neighbor: edges[cur])
        {
            inDegrees[neighbor.first]--;
            rhsConst[neighbor.first] += curVal*edges[cur][neighbor.first];
            if(inDegrees[neighbor.first]==0)
            {
                q.push(neighbor.first);
                n--;
            }
        }
    }
    return n?false:true;
}

void Graph::printOutput()
{
    cout <<"The final result is:"<<endl;
    for(auto it=rhsConst.begin();it!=rhsConst.end(); it++)
    {
        cout << it->first <<" = "<<it->second << endl;
    }
}

bool Graph::enoughEqus()
{
    return numEquations >= (int)inDegrees.size();  
}

bool Graph::invalidEqus()
{
    return invalidEquation;
}


bool Graph::isInt(const string& s)
{
    if(s.empty()||!isdigit(s[0]))
        return false;
    char* p;
    strtol(s.c_str(), &p, 10);
    return(*p == 0);
}

void Graph::initKey(const string& s)
{
    if(!edges.count(s))
    {
        edges[s]=unordered_map<string, float>();
    }

    if(!inDegrees.count(s))
    {
        inDegrees[s]= 0;
    }

    if(!rhsConst[s])
    {
        rhsConst[s]= 0;
    }
}
