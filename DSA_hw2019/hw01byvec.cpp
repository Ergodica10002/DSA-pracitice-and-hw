#include <iostream>
#include <vector>
#include <algorithm>
#define MAXLEN 200000
#define DEBUG 0
using namespace std;
int search(vector <int> &vec , int num)
{
	int upbound = vec.end() - vec.begin();
	int lowbound = 0;
	int mid = (upbound + lowbound) / 2;
	while (upbound > lowbound){
		if (num < vec[mid]){
			upbound = mid;
			mid = (upbound + lowbound) / 2;
		}else if (num > vec[mid]){
			lowbound = mid + 1;
			mid = (upbound + lowbound) / 2;
		}
		else{
			return mid;
		}
	}
	return mid;
}
void insertionSort(int* buffer, int size)
{
	for (int i = 1; i < size; i++){
		int j = i;
		int temp = buffer[i];
		while (j > 0 && buffer[j - 1] > temp){
			buffer[j] = buffer[j - 1];
			j--;
		}
		buffer[j] = temp;
	}
#ifdef DEBUG
	cout << "insertionSort result:\n";
	for (int i = 0; i < size; i++)
		cout << buffer[i] << ' ';
	cout << endl;
#endif
	return;
}
void print(int array[], int size)
{
	for (int i = 0; i < size; i++)
		cout << array[i] << ' ';
}
using namespace std;
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int N, M, K;
	cin >> N >> M >> K;
	vector <int> vec;
	vec.reserve(M);
	int window[MAXLEN];
	int element;
	for (int i = 0; i < M; i++){
		cin >> window[i];
		vec.push_back(window[i]);
	}
	sort(vec.begin(), vec.end());
	cout << vec[K - 1] << '\n';
	for (int i = M; i < N; i++){
		vector<int>::iterator pos = vec.begin() + search(vec, window[i % M]);
		vec.erase(pos);
#if DEBUG
		cout << "aftererase vec:\n";
		for (int j = 0; j < vec.end() - vec.begin(); j++){
			cout << vec.at(j) << " ";
		}
		cout << '\n';
#endif
		cin >> window[i % M];
		int insertpos = search(vec, window[i % M]);
		vec.insert(vec.begin() + insertpos, window[i % M]);
#if DEBUG
		cout << "nowvec:\n";
		for (int j = 0; j < vec.end() - vec.begin(); j++){
			cout << vec[j] << " ";
		}
		cout << '\n';
#endif
		cout << vec[K - 1] << '\n';
	}

	return 0;
}
