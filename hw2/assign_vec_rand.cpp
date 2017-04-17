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
void par_prefix_sum(int *arr, int n)
{
	if (n <= 1000) {
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

// vector<int> par_prefix_sum(vector<int> &arr)
// {

// 	int size = arr.size();
// 	int i = 0;
// 	int sum = 0;
// 	while(i < size)
// 	{
// 		sum += arr[i];
// 		arr[i] = sum;
// 		i++;
// 	}
// 	return arr;
	
// }
int *C;
int * par_randomized_cc(int n, struct edge_struct *E, int E_size,int *L)
{
	if (E_size == 1)
		return L;
	int *M ;
	// vector<int> M(n);
	int S_size = E_size+1;

	int *S = (int *)malloc(sizeof(int) * (E_size+1));
	S[0] = 0;
	S[E_size] = 0;
	// vector<int> S(E.size()+1);
	cilk_for(int i = 1; i < n; i++)
	{
		C[i] = rand() % 2 ;
	}
	cilk_for(int i = 1; i < E_size; i++)
	{
		if(C[E[i].u] == 1 && C[E[i].v] == 0)
			L[E[i].u] =  L[E[i].v];
	}
	cilk_for(int i = 1; i < E_size; i++)
	{
		S[i] = 0;
	}
	cilk_for(int i = 1; i < E_size; i++)
	{
		S[i] = L[E[i].u] != L[E[i].v] ? 1 : 0;
	}
	par_prefix_sum(S, S_size);
	int F_size =(S[E_size] + 1); 
	struct edge_struct *F = (struct edge_struct *)malloc(sizeof(struct edge_struct) * (S[E_size] + 1));

	cilk_for(int i = 1; i < E_size; i++)
	{
		if(L[E[i].u] != L[E[i].v])
		{
			F[S[i]].u = min(L[E[i].u],L[E[i].v]);
			F[S[i]].v = max(L[E[i].u],L[E[i].v]);
		}
	}
	// free(S);
	M = par_randomized_cc(n,F,F_size,L);
	// free(F);
	cilk_for(int i = 1; i < E_size; i++)
	{
		if(E[i].v == L[E[i].u])
			M[E[i].u] = M[E[i].v];
	}
	// printf("hi 6\n");
	free(S);
	free(E);
	// free(L);
	// E.clear();
	// L.clear();
	return M;
}
int print_answer(int *L,int n)
{
	map <int, int> answer;
	for (int i = 1; i < n; i++) {
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
	int *L;
	scanf("%d %d",&vertices,&edges);
	struct edge_struct *E = (struct edge_struct *)malloc(sizeof(struct edge_struct) * (edges+1));
	for( i = 1; i < edges+1; i++)
	{
		scanf("%d %d",&E[i].u,&E[i].v);
		// ////printf("%d %d \n ",E[i].u,E[i].v);

	}
	L = (int *) malloc(sizeof(int) * (vertices+1));
	// vector<int> L(vertices+1);
	for( i = 1; i < vertices+1; i++)
	{
		L[i] = i;
	}
	int n = vertices + 1;
	
	C = (int *) malloc(sizeof(int) * n);
	struct timespec ts0, ts1;
	clock_gettime(CLOCK_MONOTONIC, &ts0);
	L = par_randomized_cc(vertices+1,E,edges+1,L);
	clock_gettime(CLOCK_MONOTONIC, &ts1);
	unsigned long int tim = (ts1.tv_sec - ts0.tv_sec) * 1000000000 + (ts1.tv_nsec - ts0.tv_nsec);
	fprintf(stderr, "Time taken is %.6lf ms \n", (double)tim/1000000);

	print_answer(L,n);
}


