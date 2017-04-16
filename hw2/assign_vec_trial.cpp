#include <stdio.h>
#include <iostream>
#include <limits.h>
#include <algorithm>
#include <map>
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
int par_sum(int *arr,int n)
{
	int sum = 0;
	for(int i = 1;i < n; i++)
	{
		sum = sum + arr[i];
	}
	return sum;
}
void par_prefix_sum(int *arr, int n)
{
	if (n < 32) {
		int i = 0;
		int sum = 0;
		while(i < n)
		{
			sum += arr[i];
			arr[i] = sum;
			i++;
		}
	} else {
		int * Y = (int *) malloc(sizeof(int) * (n/2));
		for (int i = 0; i < n/2; i++) {
			Y[i] = arr[2*i] + arr[2*i+1];
		}
		par_prefix_sum(Y, n/2);
		for (int i = 1; i < n; i++) {
			if (i%2 == 1)
				arr[i] = Y[i/2];
			else
				arr[i] += Y[(i-1)/2];
		}
		free(Y);
	}

}
vector<int> find_roots(int n,vector<int> P,vector<int> S)
{
	////printf("find roots\n" );
	cilk_for(int i = 1; i < n; i++)
	{
		S[i] = P[i];
	}
	bool flag = true;
	////printf("in find hey \n");
	while (flag == true)
	{
		flag = false;
		cilk_for(int i = 1; i < n; i++)
		{
			////printf("%d\n",i );
			S[i] = S[S[i]];
			if(S[i] != S[S[i]]) 
				flag = true;
		}
	}

	return S;
}
#define ECUTOFF 1000
int * l2h;
int * h2l;

vector<int> par_deterministic_cc(int n, struct edge_struct *E, int E_size,vector<int> &L)
{
	if (E_size == 1)
		return L;

	//vector<int> l2h(n);
	//vector<int> h2l(n);
	int S_size = E_size+1;
	int *S = (int *) calloc(S_size, sizeof(int));
	//printf("S_size = %d\n", E.size() + 1);
	cilk_for(int i = 1; i < n; i++)
	{
		l2h[i] = 0;
		h2l[i] = 0;
	}
	cilk_for(int i = 1; i < E_size; i++)
	{
		if(E[i].u < E[i].v)
		{
			l2h[E[i].u] =  1;
		}
		else
		{
			h2l[E[i].u] = 1; 
		}
	}
	int n1 = par_sum(l2h,n);
	int n2 = par_sum(h2l,n);

	// printf("hey 0\n");
	//free(l2h);
	//free(h2l);
	cilk_for(int i = 1; i < E_size; i++)
	{
		if( n1 >= n2 && E[i].u < E[i].v)
			L[E[i].u] = E[i].v;
		else if( n1 < n2 && E[i].u > E[i].v)
			L[E[i].u] = E[i].v;
	}
	// printf("n1 n2 %d %d \n",n1 ,n2);
	L = find_roots(n,L,L);
	cilk_for(int i = 1; i < E_size; i++)
	{
		S[i] = L[E[i].u] != L[E[i].v] ? 1 : 0;
	}
	// printf("hey 2\n");
	S[E_size] = 0;
	par_prefix_sum(S, S_size);
	int F_size =(S[E_size] + 1); 
	// printf("hey 3\n");
	struct edge_struct *F = (struct edge_struct *)malloc(sizeof(struct edge_struct) * (S[E_size] + 1));
	// printf("hey 4\n");
	cilk_for(int i = 1; i < E_size; i++)
	{
		if(L[E[i].u] != L[E[i].v])
		{
				F[S[i]].u = min(L[E[i].u],L[E[i].v]);
				F[S[i]].v = max(L[E[i].u],L[E[i].v]);
				// //printf("F %d %d\n",F[S[i]].u,F[S[i]].v);
		}
	}
	free(S);
	free(E);
	L = par_deterministic_cc(n,F, F_size,L);
	return L;


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
	// ////printf("%d %d",vertices,edges);
	struct edge_struct *E = (struct edge_struct *)malloc(sizeof(struct edge_struct) * (edges+1));
	for( i = 1; i < edges+1; i++)
	{
		scanf("%d %d",&E[i].u,&E[i].v);
		// ////printf("%d %d \n ",E[i].u,E[i].v);

	}
	vector<int> L(vertices+1);
	for( i = 1; i < vertices+1; i++)
	{
		L[i] = i;
	}
	int n = vertices + 1;
	l2h = (int *) malloc(n * sizeof(int));
	h2l = (int *) malloc(n * sizeof(int));

	struct timespec ts0, ts1;
	clock_gettime(CLOCK_MONOTONIC, &ts0);
	L = par_deterministic_cc(vertices+1,E, edges+1,L);
	clock_gettime(CLOCK_MONOTONIC, &ts1);
	unsigned long int tim = (ts1.tv_sec - ts0.tv_sec) * 1000000000 + (ts1.tv_nsec - ts0.tv_nsec);
	fprintf(stderr, "Time taken is %.6lf ms \n", (double)tim/1000000);
	//sort(L.begin(), L.end());
	print_answer(L);
}


