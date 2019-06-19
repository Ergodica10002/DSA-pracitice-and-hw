#include <iostream>
#include <string>
#define MAXL 10000
using namespace std;
int hasht[MAXL];
int rhasht[MAXL];
int ohasht[MAXL];
int power[MAXL];
int main(void)
{
	string s, t;
	cin >> s >> t;
	int len1 = s.size();
	int len2 = t.size();
	hasht[0] = s[0] - 'a';
	for (int i = 1; i < len1; i++){
		hasht[i] = hasht[i - 1] * 26 + s[i] - 'a';
	} 
	rhasht[0] = s[len1 - 1] - 'a';
	for (int i = len1 - 2; i >= 0; i--){
		rhasht[len1 - i - 1] = rhasht[len1 - i - 2] * 26 + s[i] - 'a';
	} 		
	ohasht[0] = t[0] - 'a';
	for (int i = 1; i < len2; i++){
		ohasht[i] = ohasht[i - 1] * 26 + t[i] - 'a';
	}
	power[0] = 1; 
	for (int i = 1; i < max(len1, len2); i++){
		power[i] = power[i - 1] * 26;
	}
	int nowat = -1;
	while (nowat + 1 < len2){
	//	printf("nowat %d\n", nowat);
		bool ismove = 0;
		for (int i = len2 - 1; i > nowat; i--){
			int object = (nowat == -1)? ohasht[i] : ohasht[i] - ohasht[nowat] * power[i - nowat];
	//		printf("object %d\n", object);
			int len = i - nowat;
			bool isfound = 0;
			int init = -1, end = -1;
			if (len > len1){
				continue;
			}
			else{
				for (int j = len - 1; j < len1; j++){	//以s[j]或s[len - 1 - j]做比較字串的結尾 
					int comp1 = (j == len - 1)? hasht[j] : (hasht[j] - hasht[j - len] * power[len]);
					int comp2 = (j == len - 1)? rhasht[j] : (rhasht[j] - rhasht[j - len] * power[len]);
	//				printf("j %d comp1 %d comp2 %d\n", j, comp1, comp2);
					if (comp1 == object){
						init = j - len + 1;
						end = j;
						isfound = 1;
						break;
					} 
					if	(comp2 == object){
						init = len1 - 1 - (j - (len - 1));
						end = init - len + 1;
						isfound = 1;
						break;
					}
				}
				if (isfound){
					nowat += len;
					ismove = 1;
					cout << "init " << init + 1 << " end " << end + 1<< '\n';
					break;
				}
			}
		}
		if (!ismove){
			cout << "not found\n";
			break;
		}
			
	}
	return 0;
}
 
