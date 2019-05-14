#include <iostream>
#include <string>
#include <map>
#define MAXLEN 100000
#define mod1 7
#define mod2 11
#define NDEBUG
using namespace std;

int hashtable1[MAXLEN] = {0};
int hashtable2[MAXLEN] = {0};
int modtable1[MAXLEN] = {0};
int modtable2[MAXLEN] = {0};
void fillmod1(int tomod, int len){
	modtable1[0] = 1;
	for (int i = 1; i < len; i++){
		modtable1[i] = modtable1[i - 1] * tomod;
	}
	return;
}
void fillmod2(int tomod, int len){
	modtable2[0] = 1;
	for (int i = 1; i < len; i++){
		modtable2[i] = modtable2[i - 1] * tomod;
	}
	return;
}
void filltable1(string s, int mod){
	int hashnum = 0;
	for (int i = 0; s[i] != '\0'; i++){
		hashnum = hashnum * mod + (s[i] - 'a');
		hashtable1[i + 1] = hashnum;
	}
	return;
}
void filltable2(string s, int mod){
	int hashnum = 0;
	for (int i = 0; s[i] != '\0'; i++){
		hashnum = hashnum * mod + (s[i] - 'a');
		hashtable2[i + 1] = hashnum;
	}
	return;
}
int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	fillmod1(mod1, MAXLEN);
	fillmod2(mod2, MAXLEN);
	string s;
	int m;
	while (cin >> m){
		cin >> s;
		if (m == 0)
			break;
		filltable1(s, mod1);
		filltable2(s, mod2);
		int slen = s.size();

		bool answer_find = 0;
		
		//first task
		int result[2] = {0};
		int lowbound = 1, upbound = slen + 1;
		int mid = (lowbound + upbound) / 2;
		while(upbound - lowbound >= 1){
			map<int, int> count;
			map<int, int>::iterator it;
			for (int j = mid; j <= slen; j++){
				int hr1 = hashtable1[j] - hashtable1[j - mid] * modtable1[mid];
				if ((it = count.find(hr1)) != count.end()){
					it->second++;
					if (it->second >= m){
						answer_find = 1;
						result[0] = mid;
						result[1] = j - mid;
					}
				}
				else{
					count[hr1] = 1;
					if (m == 1){
						answer_find = 1;
						result[0] = mid;
						result[1] = j - mid;
					}
				}
			}
			if (answer_find == 1){
				lowbound = mid + 1;
				answer_find = 0;
			}
			else{
				upbound = mid;
			}
			mid = (lowbound + upbound) / 2;
		}
		if (result[0] == 0)
			cout << "none\n";
		else
			cout << result[0] << ' ' << result[1] << '\n';
		
		//second task
		answer_find = 0;
		result[0] = 0;
		int possible[MAXLEN] = {0};
		int pnum = 0;
		if (slen <= 2)
			cout << "Just a legend\n";
		else{
			for (int i = 1; i < slen; i++){
				if ((hashtable1[i] == hashtable1[slen] - hashtable1[slen - i] * modtable1[i])
					&& (hashtable2[i] == hashtable2[slen] - hashtable2[slen - i] * modtable2[i])){
					possible[pnum] = i;
					pnum++;
				}
			}
			if (pnum == 0)
				cout << "Just a legend\n";
			else{
				lowbound = 0;
				upbound = pnum;
				mid = (lowbound + upbound) / 2;
				while (upbound - lowbound >= 1){
					for (int j = 1; j + possible[mid] < slen; j++){
						int hr1 = hashtable1[j + possible[mid]] - hashtable1[j] * modtable1[possible[mid]];
						int hr2 = hashtable2[j + possible[mid]] - hashtable2[j] * modtable2[possible[mid]];
						if ((hr1 == hashtable1[possible[mid]]) && (hr2 == hashtable2[possible[mid]])){
							result[0] = possible[mid];
							answer_find = 1;
							break;
						}
					}
					if (answer_find == 1){
						lowbound = mid + 1;
					}
					else{
						upbound = mid;
					}
					answer_find = 0;
					mid = (lowbound + upbound) / 2;
				}
				if (result[0] == 0)
					cout << "Just a legend\n";
				else{
					for (int i = 0; i < result[0]; i++)
						cout << s[i];
					cout << '\n';
				}
			}
		}
	}


	return 0;
}

