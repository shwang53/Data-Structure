/* Your code here! */
/* Your code here! */
/**
 * @file dsets.h
 */

#pragma once
#include <vector>
using namespace std;

class DisjointSets
{
	public:
	//	DisjointSets ();
		void addelements (int n);
		int find (int e);
		void setunion (int a, int b);
		int size (int e);

	private:
		vector<int> noname;

};
