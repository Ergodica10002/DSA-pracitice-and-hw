#include <iostream>
#include <deque>
#include <algorithm>
#define MAXLEN 200000
#define DEBUG 0
using namespace std;
int search(deque <int> &sorted, int M, int num)
{
	int upbound = M;
	int lowbound = 0;
	int mid = (upbound + lowbound) / 2;
	while (upbound > lowbound){
		if (num < sorted[mid]){
			upbound = mid;
			mid = (upbound + lowbound) / 2;
		}else if (num > sorted[mid]){
			lowbound = mid + 1;
			mid = (upbound + lowbound) / 2;
		}
		else{
			return mid;
		}
	}
	return mid;
}
void printqueue(deque <int> sorted, int M){
	for (int i = 0; i < M; i++)
		cout << "test:" << sorted[i] << '\n';
	return;
}
int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int N, M, K;
	cin >> N >> M >> K;
	int window[MAXLEN];
	deque <int> sorted(M + 1, 2147483647);
	for (int i = 0; i < M; i++){
		cin >> window[i];
		sorted[i] = window[i];
	}
	sort(sorted.begin(), sorted.begin() + M);
	cout << sorted[K - 1] << '\n';
	for (int i = M; i < N; i++){
		deque<int>::iterator pos = sorted.begin() + search(sorted, M, window[i % M]);
		sorted.erase(pos);
#if DEBUG
		cout << "aftererase:\n";
		printqueue(sorted, M);
#endif
		cin >> window[i % M];
		int insertpos = search(sorted, M, window[i % M]);
		sorted.insert(sorted.begin() + insertpos, window[i % M]);
#if DEBUG
		cout << "afterinsert:\n";
		printqueue(sorted, M);
#endif		
		cout << sorted[K - 1] << '\n';
	}


	return 0;
}

