#include <iostream>
#include <vector>
#define MAXLEN 200000
using namespace std;
void insert(int element, int array[], int n){
	int i = n;
	while (i > 0 && element < array[i - 1]){
		array[i] = array[i - 1];
		i--;
	}
	array[i] = element;
	return;
}
void del(int element, int array[], int n){
	int upbound = n, lowbound = 0;
	int mid = (upbound + lowbound) / 2;
	while (array[mid] != element){
		if (upbound == lowbound)
			return;
		if (array[mid] > element){
			upbound = mid;
			mid = (upbound + lowbound) / 2;
		}else{
			lowbound = mid;
			mid = (upbound + lowbound) / 2;
		}
	}
	for (int i = mid; i < n - 1; i++){
		array[i] = array[i + 1];
	}
	return;
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
	int N, M, K;
	cin >> N >> M >> K;
	int array[MAXLEN];
	int window[MAXLEN];
	int element;
	for (int i = 0; i < M; i++){
		cin >> window[i];
		array[i] = window[i];
	}
	insertionSort(array, M);
	cout << array[K - 1] << endl;
	for (int i = M; i < N; i++){
		del(window[i % M], array, M);
		cin >> window[i % M];
		insert(window[i % M], array, M - 1);
#ifdef DEBUG
		print(array, M);
#endif
		cout << array[K - 1] << endl;
	}

	return 0;
}
