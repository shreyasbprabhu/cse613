#include <stdio.h>
#include <iostream>
#include <limits.h>
#include <algorithm>
#include <cilk/cilk.h>
#include <time.h>
#include <math.h>
#include <vector>
#include <map>
using namespace std;

struct edge_struct
{
	int u;
	int v;
};

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
	return arr;
	
}
int *C;
vector<int> par_randomized_cc(int n,vector<edge_struct> &E,vector<int> &L)
{
	if (E.size() == 1)
		return L;
	vector<int> M(n);
	vector<int> S(E.size()+1);
	cilk_for(int i = 1; i < n; i++)
	{
		C[i] = rand() % 2 ;
	}
	cilk_for(int i = 1; i < E.size(); i++)
	{
		if(C[E[i].u] == 1 && C[E[i].v] == 0)
			L[E[i].u] =  L[E[i].v];
	}
	cilk_for(int i = 1; i < E.size(); i++)
	{
		S[i] = L[E[i].u] != L[E[i].v] ? 1 : 0;
	}
	S = par_prefix_sum(S);
	vector<edge_struct> F(S[E.size()]+1);
	cilk_for(int i = 1; i < E.size(); i++)
	{
		if(L[E[i].u] != L[E[i].v])
		{
			F[S[i]].u = min(L[E[i].u],L[E[i].v]);
			F[S[i]].v = max(L[E[i].u],L[E[i].v]);
		}
	}
	M = par_randomized_cc(n,F,L);
	cilk_for(int i = 1; i < E.size(); i++)
	{
		if(E[i].v == L[E[i].u])
			M[E[i].u] = M[E[i].v];
	}
	return M;
}
int print_answer(vector<int> &L)
{
	map <int, int> answer;
	for (int i = 1; i < L.size(); i++) {
		answer[L[i]] ++;
	}
	printf("%d\n", answer.size());
	vector<int>ans;
	for (map<int,int>::iterator iter = answer.begin(); iter != answer.end(); ++iter) {

		ans.push_back(iter->second);
	}
	sort(ans.begin(), ans.end());
	for (int i = ans.size()-1; i >=0; i--) {
		printf("%d\n", ans[i]);
	}
}
int main()
{
	int vertices;
	int edges;
	int i = 0;
	scanf("%d %d",&vertices,&edges);
	vector<edge_struct> E(edges+1);
	for( i = 1; i < edges+1; i++)
	{
		scanf("%d %d",&E[i].u,&E[i].v);
	}
	vector<int> L(vertices+1);
	for( i = 1; i < vertices+1; i++)
	{
		L[i] = i;
	}
	int n = vertices + 1;
	
	C = (int *) malloc(sizeof(int) * n);

	struct timespec ts0, ts1;
	clock_gettime(CLOCK_MONOTONIC, &ts0);
	L = par_randomized_cc(vertices+1,E,L);

	clock_gettime(CLOCK_MONOTONIC, &ts1);
	unsigned long int tim = (ts1.tv_sec - ts0.tv_sec) * 1000000000 + (ts1.tv_nsec - ts0.tv_nsec);
	fprintf(stderr, "Time taken is %.6lf ms \n", (double)tim/1000000);

	print_answer(L);
}


