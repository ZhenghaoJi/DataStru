#pragma once
#include<iostream>
#include<stack>
#include<queue>
#include<fstream>
#include<vector>
#include<string>

#define MaxV 100 //at most 100 verticle
#define Maxint 99999
using namespace std;

int NV=MaxV;
vector<vector<int>> cost(MaxV,vector<int>(MaxV,Maxint));
vector<string> place;
vector<string> note;
void ReadCostAndPlace()
{
	ifstream fin("cost.txt", ios::in);
	int nv;
	fin >> nv;
	NV = nv;//SAVE NV

	ifstream fpin("place.txt", ios::in);
	int num;
	string name;
	string str;
	for (int i = 0; i < nv; i++)
	{
		for (int j = 0; j < nv; j++)
		{
			int tem;
			fin >> tem;
			if (tem<0)
			{
				cost[i][j] = Maxint;
			}
			else
			{
				cost[i][j] = tem;
			}
			
		}
	}
	for (int i = 0; i < nv; i++)
	{
		fpin >> num >> name >> str;
		place.push_back(name);
		note.push_back(str);
	}

}