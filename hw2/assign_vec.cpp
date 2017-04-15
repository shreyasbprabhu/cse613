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
	for(int i = 1;i < n; i++)
	{
		sum = sum + arr[i];
	}
	return sum;
}
// vector
vector<int> par_prefix_sum(vector<int> &arr)
{

	int size = arr.size();
	int i = 0;
	int sum = 0;
	while(i < size)
	{
		sum += arr[i];
		arr[i] = sum;
		i++;
	}
	// if(arr.size() == 1)
	// 	return 
	return arr;
	
}
vector<int> find_roots(int n,vector<int> P,vector<int> S)
{
	//printf("find roots\n" );
	cilk_for(int i = 1; i < n; i++)
	{
		S[i] = P[i];
	}
	bool flag = true;
	//printf("in find hey \n");
	while (flag == true)
	{
		flag = false;
		cilk_for(int i = 1; i < n; i++)
		{
			//printf("%d\n",i );
			S[i] = S[S[i]];
			if(S[i] != S[S[i]]) 
				flag = true;
		}
	}

	return S;
}
vector<int> par_deterministic_cc(int n,vector<edge_struct> &E,vector<int> &L)
{
	if (E.size() == 0)
		return L;
	vector<int> l2h(n);
	vector<int> h2l(n);
	vector<int> S(E.size());
	cilk_for(int i = 1; i < n; i++)
	{
		l2h[i] = 0;
		h2l[i] = 0;
	}
	cilk_for(int i = 0; i < E.size(); i++)
	{
		if(E[i].u < E[i].v)
			l2h[E[i].u] =  1;
		else
			h2l[E[i].u] = 1; 
	}
	int n1 = par_sum(l2h,n+1);
	int n2 = par_sum(h2l,n+1);
	cilk_for(int i = 0; i < E.size(); i++)
	{
		if( n1 >= n2 && E[i].u < E[i].v)
			L[E[i].u] = E[i].v;
		else if( n1 < n2 && E[i].u > E[i].v)
			L[E[i].u] = E[i].v;
	}
	//printf("hey \n");
	L = find_roots(n,L,L);
	//printf("hii\n");
	cilk_for(int i = 0; i < E.size(); i++)
	{
		S[i] = L[E[i].u] != L[E[i].v] ? 1 : 0;
	}
	//printf("hii 2 \n");
	S = par_prefix_sum(S);
	//printf("hii 3\n");
	//printf("%d\n",E.size());
	vector<edge_struct> F(S[E.size()-1]);
	//printf("hii 4 \n");

	for(int i = 0; i < S.size() ; i ++ )
		//printf("S[%d] %d\n",i,S[i] );

	//printf("ddone with s[i]\n");
	cilk_for(int i = 0; i < E.size(); i++)
	{
		if(L[E[i].u] != L[E[i].v])
		{
				F[S[i]].u = L[E[i].u];
				F[S[i]].v = L[E[i].v];
				printf("F %d %d\n",F[S[i]].u,F[S[i]].v);
		}
	}
	//printf("hii 5 \n");
	L = par_deterministic_cc(n,F,L);
	for(int i = 0; i < L.size() ; i ++ )
		printf("L[%d] %d\n",i,L[i] );
	return L;


}
int main()
{
	int vertices;
	int edges;
	int i = 0;
	scanf("%d %d",&vertices,&edges);
	// //printf("%d %d",vertices,edges);
	vector<edge_struct> E(edges);
	for( i = 0; i < edges; i++)
	{
		scanf("%d %d",&E[i].u,&E[i].v);
		// //printf("%d %d \n ",E[i].u,E[i].v);

	}
	vector<int> L(vertices+1);
	for( i = 1; i < vertices+1; i++)
	{
		L[i] = i;
	}
	
	L = par_deterministic_cc(vertices+1,E,L);
	for(int i = 0; i < L.size() ; i ++ )
		printf("L[%d] %d\n",i,L[i] );
}


