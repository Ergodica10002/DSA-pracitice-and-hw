#include <iostream>
#define MAXN 20000000 
using namespace std;
int seesaw[MAXN];
int tor(int n){
	int s = 0;
	for (int i = 0; i < n; i++){
		s += seesaw[i] * (i + 1);
	}
	return s;
}
int main(void)
{
	int n;
	cin >> n;
	int sum = 0;
	for (int i = 0; i < n; i++){
		cin >> seesaw[i];
		sum += seesaw[i];
	}
	int s = tor(n);
	if (s % sum == 0){
		cout << seesaw[0];
		for (int j = 1; j < n; j++){
			if (j == s / sum - 1)
				cout << " v";
			else
				cout << ' ' << seesaw[j];
		}
	}
	else{
		for (int i = 0; i < n / 2; i++){
			int temp = seesaw[i];
			seesaw[i] = seesaw[n - i - 1];
			seesaw[n - i - 1] = temp;
			s = tor(n);
			if (s % sum == 0){
				cout << seesaw[0];
				for (int j = 1; j < n; j++){
					if (j == s / sum - 1)
						cout << " v";
					else
						cout << ' ' << seesaw[j];
				}
				break;
			}
		}
	}
	


	return 0;
}

