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
// vector
// vector<int> parallel_prefix_sum(vector<int> &arr)
// {
// 	vector<int> S(arr.size());
// 	if(arr.size() == 1)
// 		S[0] = arr[0];
// 	else
// 	{
// 		vector<int> y(arr.size()/2);
// 		cilk_for(int i = 1; i < n/2 ;i++ )
// 		{
// 			y[i]  = arr[2*i-1] + arr[2*i];
// 		}
// 		vecto<int> Z(arr.size()/2) = parallel_prefix_sum(y);
// 		cilk_for(int i = 1;i <= n; i++)
// 		{
// 			if(i == 1)
// 				S[1] = arr[1];
// 			else if(i%2 == 0)
// 				S[i] = Z[i/2];
// 			else
// 				S[i] = Z[(i-1)/2] + arr[i];		
// 		} 
// 	}
// 	return S; 

// }
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
vector<int> par_deterministic_cc(int n,vector<edge_struct> &E,vector<int> &L)
{
	if (E.size() == 1)
		return L;

	//vector<int> l2h(n);
	//vector<int> h2l(n);
	int * l2h = (int *) malloc(n * sizeof(int));
	int * h2l = (int *) malloc(n * sizeof(int));
	vector<int> S(E.size()+1);
	cilk_for(int i = 1; i < n; i++)
	{
		l2h[i] = 0;
		h2l[i] = 0;
	}
	cilk_for(int i = 1; i < E.size(); i++)
	{
		if(E[i].u < E[i].v)
			l2h[E[i].u] =  1;
		else
			h2l[E[i].u] = 1; 
	}
	int n1 = par_sum(l2h,n);
	int n2 = par_sum(h2l,n);
	free(l2h);
	free(h2l);
	cilk_for(int i = 1; i < E.size(); i++)
	{
		if( n1 >= n2 && E[i].u < E[i].v)
			L[E[i].u] = E[i].v;
		else if( n1 < n2 && E[i].u > E[i].v)
			L[E[i].u] = E[i].v;
	}
	////printf("hey \n");
	L = find_roots(n,L,L);
	//printf("after find roots\n");
	// for(int i = 0; i < L.size() ; i ++ )
		//printf("L[%d] %d\n",i,L[i] );
	////printf("hii\n");
	cilk_for(int i = 1; i < E.size(); i++)
	{
		S[i] = L[E[i].u] != L[E[i].v] ? 1 : 0;
	}
	////printf("hii 2 \n");
	S = par_prefix_sum(S);
	////printf("hii 3\n");
	////printf("%d\n",E.size());
	vector<edge_struct> F(S[E.size()]+1);
	////printf("hii 4 \n");

	// for(int i = 0; i < S.size() ; i ++ )
		////printf("S[%d] %d\n",i,S[i] );

	////printf("ddone with s[i]\n");
	cilk_for(int i = 1; i < E.size(); i++)
	{
		if(L[E[i].u] != L[E[i].v])
		{
				F[S[i]].u = L[E[i].u];
				F[S[i]].v = L[E[i].v];
				// //printf("F %d %d\n",F[S[i]].u,F[S[i]].v);
		}
	}
	////printf("hii 5 \n");
	L = par_deterministic_cc(n,F,L);
	// for(int i = 0; i < L.size() ; i ++ )
		// //printf("L[%d] %d\n",i,L[i] );
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
	vector<edge_struct> E(edges+1);
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
	for( i = 0; i < edges; i++)
	{
		//printf("%d %d \n ",E[i].u,E[i].v);		
	}

	struct timespec ts0, ts1;
	clock_gettime(CLOCK_MONOTONIC, &ts0);
	L = par_deterministic_cc(vertices+1,E,L);
	clock_gettime(CLOCK_MONOTONIC, &ts1);
	unsigned long int tim = (ts1.tv_sec - ts0.tv_sec) * 1000000000 + (ts1.tv_nsec - ts0.tv_nsec);
	fprintf(stderr, "Time taken is %.6lf ms \n", (double)tim/1000000);
	//sort(L.begin(), L.end());
	print_answer(L);
}


