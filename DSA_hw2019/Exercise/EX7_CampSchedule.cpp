#include <iostream>
using namespace std;
int main(void)
{
	string s, t;
	cin >> s >> t;
	int lens = s.size();
	int lent = t.size();
	int socnt = 0, tocnt = 0;
	for (int i = 0; i < lens; i++){
		if (s[i] == '1')
			socnt++;
	}
	for (int i = 0; i < lent; i++){
		if (t[i] == '1')
			tocnt++;
	}
	printf("socnt %d tocnt %d\n", socnt, tocnt);
	int hash[1000];
	hash[0] = t[0] - '0';
	for (int i = 1; i < lent; i++){
		hash[i] = hash[i - 1] * 2 + t[i] - '0';
	}
	int power[1000];
	power[0] = 1;
	for (int i = 1; i < lent; i++){
		power[i] = power[i - 1] * 2;
	}
	int tomove = -1;
	for (int i = 1; i < lent; i++){
		int hcode1 = hash[lent - 1] - hash[i - 1] * power[lent - i];
		int hcode2 = hash[lent - i - 1];
		printf("i %d code1 %d code2 %d\n", i, hcode1, hcode2);
		if (hcode1 == hcode2){
			tomove = i;
			break;
		}
	}
	printf("tomove = %d\n", tomove);
	if (tomove == -1){
		int number = socnt / tocnt;
		int szcnt = lens - socnt;
		while (number > 0){
			cout << t;
			number--;
			socnt -= tocnt;
			szcnt -= (lent - tocnt);
		}
		for (int i = 0; i < socnt; i++)
			cout << '1';
		for (int i = 0; i < szcnt; i++)
			cout << '0';
	}
	else{
		cout << t;
		socnt -= tocnt;
		lens -= lent;
		int szcnt = lens - socnt;
		while (szcnt > 0 && socnt > 0){		
			for (int i = lent - tomove ; i < lent; i++){
				cout << t[i];
				if (t[i] == '1')
					socnt--;
				else
					szcnt--;
				if (szcnt == 0 || socnt == 0)
					break;
			}
		}
		while(socnt > 0){
			cout << '1';
			socnt--;
		}
		while (szcnt > 0){
			cout << '0';
			szcnt--;
		}
	}
	return 0;
}

