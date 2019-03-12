#include <iostream>
#include <set>
#include <algorithm>
#define MAXLEN 200000
#define NDEBUG 

using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int N, M, K;
	cin >> N >> M >> K;
	multiset<int> sorted;
	int window[M];
	int element;
	for (int i = 0; i < M; i++){
		cin >> window[i];
		sorted.insert(window[i]);
	}
	multiset<int>::iterator toprint = sorted.begin();
	advance(toprint, K - 1);
	cout << *toprint << '\n';
	for (int i = M; i < N; i++){
		int last_element = window[i % M];
		cin >> window[i % M];
		int new_element = window[i % M];
		if (K == 1 || K == M){
			multiset<int>::iterator erasepos = sorted.lower_bound(last_element);
			sorted.erase(erasepos);
			multiset<int>::iterator insertpos = sorted.lower_bound(new_element);
			sorted.insert(insertpos, new_element);
			if (K == 1)
				toprint = sorted.begin();
			else{
				toprint = sorted.end();
				toprint--;
			}
		}
		else{
			multiset<int>::iterator another_end = sorted.end();
			multiset<int>::iterator erasepos = sorted.lower_bound(last_element);
			if (erasepos == toprint && toprint != --another_end){
				toprint++;
			}
			else if (last_element <= *toprint && toprint != --another_end){
				toprint++;
			}
			sorted.erase(erasepos);
#ifndef NDEBUG
			cout << "aftererase " << *toprint << '\n';
#endif
			multiset<int>::iterator insertpos = sorted.lower_bound(new_element);
			if (insertpos == toprint && toprint != sorted.begin()){
				sorted.insert(insertpos, window[i % M]);
				toprint--;	
			}
			else if (new_element <= *toprint && toprint != sorted.begin()){
				sorted.insert(insertpos, window[i % M]);
				toprint--;
			}
			else
				sorted.insert(insertpos, window[i % M]);
		}
		cout << *toprint << '\n';
	}

	return 0;
}
