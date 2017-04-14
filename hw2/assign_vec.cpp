#include <stdio.h>
#include <iostream>
#include <limits.h>
#include <algorithm>
#include <cilk/cilk.h>
#include <time.h>
#include <math.h>
#include <vector>
using namespace std;

struct edge_struct
{
	int u;
	int v;
};
int par_sum(vector<int> &arr,int n)
{
	int sum = 0;
	for(int i = 0;i < n; i++)
	{
		sum = sum + arr[i];
	}
	return sum;
}
vector<int> par_deterministic_cc(int n,int edges,vector<edge_struct> &E,vector<int> &L)
{
	if (edges == 0)
		return L;
	vector<int> l2h(n);
	vector<int> h2l(n);
	vector<int> S(edges);
	cilk_for(int i = 0; i < n; i++)
	{
		l2h[i] = 0;
		h2l[i] = 0;


	}
	cilk_for(int i = 0; i < edges; i++)
	{
		if(E[i].u < E[i].v)
			l2h[E[i].u] =  1;
		else
			h2l[E[i].u] = 1; 
	}
	int n1 = par_sum(l2h,n);
	int n2 = par_sum(h2l,n);
	cilk_for(int i = 0; i < edges; i++)
	{
		if( n1 >= n2 && E[i].u < E[i].v)
			L[E[i].u] = E[i].v;
		else if( n1 < n2 && E[i].u > E[i].v)
			L[E[i].u] = E[i].v;
	}
}
int main()
{
	int vertices;
	int edges;
	int i = 0;
	scanf("%d %d",&vertices,&edges);
	printf("%d %d",vertices,edges);
	vector<edge_struct> E(edges);
	for( i = 0; i < edges; i++)
	{
		scanf("%d %d",&E[i].u,&E[i].v);
		printf("%d %d",E[i].u,E[i].v);

	}
	vector<int> L(vertices);
	for( i = 0; i < vertices; i++)
	{
		L[i] = i;
	}
	
	par_deterministic_cc(vertices,edges,E,L);
}

